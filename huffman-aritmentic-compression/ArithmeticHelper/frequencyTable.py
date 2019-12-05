class FrequencyTable():
	
	def __init__(self, freqs):
		self.frequencies = list(freqs)  # Make copy
		self.frequency_sum = sum(self.frequencies) # total number of characters
		self.cumulative = None # cumulative frequency array
	
	
	def get_legth(self):
		return len(self.frequencies)
	
	# getter for getting a frequency of an element 
	def get(self, symbol):
		self.isValid(symbol)
		return self.frequencies[symbol]
	
	# setter for setting frequency of an element
	def set(self, symbol, freq):
		self.isValid(symbol)
		temp = self.frequency_sum - self.frequencies[symbol]
		self.frequency_sum = temp + freq
		self.frequencies[symbol] = freq
		self.cumulative = None
	
	# increment frequency of an element
	def increment(self, symbol):
		self.isValid(symbol)
		self.frequency_sum += 1
		self.frequencies[symbol] += 1
		self.cumulative = None
	
	# get total number of characters
	def get_frequency_sum(self):
		return self.frequency_sum
	
	# get lower bound of cumulative frequency
	def get_low(self, symbol):
		self.isValid(symbol)
		if self.cumulative is None:
			self.create_cumulative_frequency_list()
		return self.cumulative[symbol]
	
	# get higher bound of cumulative frequency
	def get_high(self, symbol):
		self.isValid(symbol)
		if self.cumulative is None:
			self.create_cumulative_frequency_list()
		return self.cumulative[symbol + 1]
	
	# create an array of cumulative frequency
	def create_cumulative_frequency_list(self):
		cumulative_frequency_list = [0]
		_sum = 0
		for freq in self.frequencies:
			_sum += freq
			cumulative_frequency_list.append(_sum)
		
		self.cumulative = cumulative_frequency_list
	
	
	# check if a input value in this table is valid or not
	def isValid(self, symbol):
		if symbol <= 256:
			return
		else:
			raise ValueError("Only supports utf-8", symbol)
	