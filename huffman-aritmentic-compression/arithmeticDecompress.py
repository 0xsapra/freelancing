from ArithmeticHelper.frequencyTable import FrequencyTable

class ArithmeticDecoder():
    
    def __init__(self, precision, _input):

        self.precision = precision # Integer specifying number of bits in 1 character. so 16 means 1 character = 16 bits which is also called UTF-16
        self.stripBits = (2 ** (precision) ) - 1 # used to mask unwanted underflowing bits
        self.half = (2 ** (precision) ) // 2 # middle of high and low
        self.quarter = self.half // 2 
        self.upper_bound = (2 ** (precision) ) - 1 # initial Higher range
        self.lower_bound = 0 # initial Lower range
        self.input = _input # input stream to read compressed data from
        self.fraction = 0 # calculate next precision bit encoded fraction from input stream
        for _ in range(self.precision):
            temp = self.fraction << 1
            self.fraction = temp | self.read_next()
    
    # Decodes the next char based on the given frequency table.
    def read(self, freqs):

        freq_sum = freqs.get_frequency_sum() # get total length of input including EOF and while space
        newrange = self.upper_bound - self.lower_bound + 1 
        offset = self.fraction - self.lower_bound # calculate offset of fraction from lower range
        value = ((offset + 1) * freq_sum - 1) // newrange
        
        start = 0
        end   = freqs.get_legth()
        # use bisection to find appropriate value for char to split onto
        while end - start > 1:
            middle = (start + end) // 2
            if freqs.get_low(middle) > value:
                end = middle
            else:
                start = middle
        
        char = start
        
        self.update(freqs, char)
        if not (self.lower_bound <= self.fraction <= self.upper_bound):
            raise AssertionError("Fraction out of range")
        return char
    
    def update(self, freqs, char):
        
        
        freq_sum = freqs.get_frequency_sum() # get total length of input including EOF and while space
        cumm_low = freqs.get_low(char) # get lower cumulative bound for current char 'char'
        cumm_high = freqs.get_high(char) # get upper cumulative bound for current char 'char'

        if cumm_low == cumm_high:
            raise Error("Frequency of this char is 0 in table")
        
        # Update range
        newrange = self.upper_bound - self.lower_bound + 1
        self.upper_bound = self.lower_bound + cumm_high * newrange // freq_sum - 1
        self.lower_bound = self.lower_bound + cumm_low  * newrange // freq_sum
        
        # output to file until low and high have same top bit 
        while ((self.lower_bound ^ self.upper_bound) & self.half) == 0:
            self.fraction = ((self.fraction << 1) & self.stripBits) | self.read_next()
            self.lower_bound  = ((self.lower_bound  << 1) & self.stripBits)
            self.upper_bound = ((self.upper_bound << 1) & self.stripBits) | 1
        # Now low's top bit must be 0 and high's top bit must be 1
        
        # While low's top two bits are 01 and high's are 10, delete the second highest bit of both
        while (self.lower_bound & ~self.upper_bound & self.quarter) != 0:
            self.fraction = (self.fraction & self.half) | ((self.fraction << 1) & (self.stripBits >> 1)) | self.read_next()
            self.lower_bound = (self.lower_bound << 1) ^ self.half
            self.upper_bound = ((self.upper_bound ^ self.half) << 1) | self.half | 1
    
    # read next value(0/1) from input stream.
    def read_next(self):
        temp = self.input.read()
        if temp == -1: # EOF
            temp = 0
        return temp


def read_frequencies(bitin):
    precision = 32
    length = bitin.read_precision() # read 1 16bit character from input file which indicates length of freq table
    res_dict = {}
    for i in range(length):
        key = bitin.read_precision() # read next 16bit character which indicated a key to dict
        value = bitin.read_precision() # read next 16bit character which indicated a value to dict
        res_dict[key] = value # assign key value to new dict to form frequency table

    res_dict[0]=0

    freqs = [res_dict[_] if _ in res_dict else 0 for _ in range(256)] # initilize freq table using dict
    freqs.append(1)  # EOF
    return FrequencyTable(freqs)


def decompress(freqs, bitin, out):
    dec = ArithmeticDecoder(32, bitin) # initialize ArithmeticDecoder with 16bit precision
    while True:
        char = dec.read(freqs)
        if char == 256:  # EOF
            break
        out.write(bytes((char,)))


