

# base class to mimic methods required in derived class
class BitStream(object):

	def read(self):
		raise NotImplementedError()

	def write(self):
		raise NotImplementedError()

	def close(self):
		raise NotImplementedError()

# Class to Read data from a stream in Big Endian format
class InputStream(BitStream):
	

	def __init__(self, inp, precision):
		self.input = inp # Input stream
		self.precision = precision # Integer specifying number of bits in 1 character. so 16 means 1 character = 16 bits which is also called UTF-16
		self.bytesRead = 0 # 1 character = precision number of bits. So we need to read precision number of bits to get 1 character.
		# bytesRead stores how many bits have we read from stream 
		self.bitsUnread = 0 # bitsUnread stores bits remaining to complete 1 character(bitsUnread = precision - bitsRead)
		
	
	# Read 1 bit from the Input stream
	def read(self):
		if self.bytesRead == -1:
			return -1
		if self.bitsUnread == 0:
			temp = self.input.read(1)
			if len(temp) == 0:
				self.bytesRead = -1
				return -1
			self.bytesRead = temp[0]
			self.bitsUnread = 8
		assert self.bitsUnread > 0
		self.bitsUnread -= 1
		return (self.bytesRead >> self.bitsUnread) & 1
	
	# read precision number of bits from input stream and output a character
	def read_precision(self):
		res = 0
		for _ in range(self.precision):
			res = (res << 1) | self.read_no_eof()
		return res


	# read until EOF(End of file) is reached
	def read_no_eof(self):
		read_bit = self.read()
		if read_bit != -1:
			return read_bit
		else:
			raise EOFError()
	
	# close the input stream pointer
	def close(self):
		self.input.close()
		self.bytesRead = -1
		self.bitsUnread = 0

# class to write data to Output stream in Big Endian format
class OutputStream(BitStream):
	
	def __init__(self, out, precision):
		self.output = out  # Output stream
		self.precision = precision # Integer specifying number of bits in 1 character. so 16 means 1 character = 16 bits which is also called UTF-16
		self.bitsRead = 0
		self.bitsFilled = 0 # bitsFilled stores bits filled to complete 1 character
		

	# write precision number of bits into output stream
	# so with precision of 16, a character "a" will write "0000 0000 0000 0097" 16 bits onto output stream
	def write_precision(self, value):
		for i in reversed(range(self.precision)):
			self.write((value >> i) & 1)
	
	# write single bit to out file
	def write(self, b):
		if b not in (0, 1):
			raise ValueError("Argument must be 0 or 1")
		self.bitsRead = (self.bitsRead << 1) | b
		self.bitsFilled += 1
		if self.bitsFilled == 8:
			towrite = bytes((self.bitsRead,))
			self.output.write(towrite)
			self.bitsRead = 0
			self.bitsFilled = 0
	
	
	# Fill output stream with remaining bits and close the stream
	def close(self):
		while self.bitsFilled != 0:
			self.write(0)
		self.output.close()
