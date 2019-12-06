from selenium import webdriver
from selenium.webdriver.chrome.options import Options


class Browser(object):

	def __init__(self, platform):
		self.platform = platform


	def init_browser(self, platform):
		raise NotImplementedError()

	def set_cookie(self, cookie_dict):
		raise NotImplementedError()

	def get_cookie(self):
		raise NotImplementedError()

	def get(self, url):
		raise NotImplementedError()

	def post(self, url, data):
		raise NotImplementedError()


class ChromeBrowser(Browser):

	def __init__(self, platform):
		super(ChromeBrowser, self).__init__(platform)
		self.init_browser()

	def init_browser(self):
		driverPath 	 = f"./bin/chromedriver-{self.platform}"

		options 	 = Options()
		options.add_argument('--headless')
		options.add_argument('—-timeout=30000')
		options.add_argument('--no-sandbox')
		options.add_argument('--ignore-certificate-errors')

		self.browser = webdriver.Chrome(driverPath, options=options)

	def set_cookie(self, cookie_dict):
		self.get("https://www.roblox.com") # changeeeeeeee krna
		assert isinstance(cookie_dict, dict)
		self.browser.add_cookie(cookie_dict)
		self.cookies = cookie_dict

	def get(self, url):
		self.browser.get(url)
		_response_text = self.browser.page_source
		return _response_text



