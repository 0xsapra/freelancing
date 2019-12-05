from ArithmeticHelper.frequencyTable import FrequencyTable

class ArithmeticEncoder():
    
    def __init__(self, precision, out):
        self.precision = precision # Integer specifying number of bits in 1 character. so 16 means 1 character = 16 bits which is also called UTF-16
        self.stripBits = (2 ** (precision) ) - 1 # used to mask unwanted underflowing bits
        self.lower_bound = 0 # initial Lower range
        self.upper_bound = (2 ** (precision) ) - 1 # initial Higher range
        self.half = (2 ** (precision) ) // 2 # middle of high and low
        self.quarter = self.half // 2  # Can be zero
        self.out = out # output file stream
        self.bit_to_write_to_stream = 0 # overflowing bit to write to stream
    
    
    def write(self, freqs, char):
        
        freq_sum = freqs.get_frequency_sum() # get total length of input including EOF and while space
        cumm_low = freqs.get_low(char) # get lower cumulative bound for current char 'char'
        cumm_high = freqs.get_high(char) # get upper cumulative bound for current char 'char'

        if cumm_low == cumm_high:
            raise Error("Frequency of this char is 0 in table")
        
        newrange = self.upper_bound - self.lower_bound + 1
        # Update range
        self.upper_bound = self.lower_bound + cumm_high * newrange // freq_sum - 1
        self.lower_bound  = self.lower_bound + cumm_low  * newrange // freq_sum
        
        # output to file until low and high have same top bit 
        while ((self.lower_bound ^ self.upper_bound) & self.half) == 0:
            bit = self.lower_bound >> (self.precision - 1)
            self.out.write(bit)

            for _ in range(self.bit_to_write_to_stream):
                self.out.write(bit ^ 1)
                self.bit_to_write_to_stream = 0

            self.lower_bound  = ((self.lower_bound  << 1) & self.stripBits)
            self.upper_bound = ((self.upper_bound << 1) & self.stripBits) | 1
        # Now low's top bit must be 0 and high's top bit must be 1
        
        # While low's top two bits are 01 and high's are 10, delete the second highest bit of both
        while (self.lower_bound & ~self.upper_bound & self.quarter) != 0:
            self.bit_to_write_to_stream += 1
            self.lower_bound = (self.lower_bound << 1) ^ self.half
            self.upper_bound = ((self.upper_bound ^ self.half) << 1) | self.half | 1



def read_and_write_frequencyTable(data, outStream):

    table = FrequencyTable([0] * 257) # initialize frequency table with 256 possible ascii range
    valueDict = {}

     # Fill frequency table
    for i in data:
        if not i in valueDict:
            valueDict[i] = 0
        valueDict[i] += 1
        table.increment(i)

    valueDict[256] = 1

    table.increment(256) # ADD EOF

    outStream.write_precision(len(valueDict))
    # output key frequency of frequency table into output file
    for key in valueDict:
        outStream.write_precision(key) # key
        outStream.write_precision(valueDict[key]) # frequency
    return table


def compress(data, outStream):

    compressor = ArithmeticEncoder(32, outStream) # initialize ArithmeticEncoder with 16bit precision
    table = read_and_write_frequencyTable(data, outStream) # calculate frequency table from data and output to output stream

    # compress each element of userInput data and write to out stream
    for i in data:
        compressor.write(table, i)

    compressor.write(table, 256)  # Declare EOF using character 256
    outStream.write(1) # Flush remaining code bits

