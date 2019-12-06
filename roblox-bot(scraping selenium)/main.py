# DONOT SUPPORT WINDOWS CURRENTLY


import sys

from browser 	import ChromeBrowser
from utils 		import *



def main():
	operatingSystem = "mac" if sys.platform == "darwin" else "linux"
	chrome = ChromeBrowser(operatingSystem)
	cookies = get_cookies()
	chrome.set_cookie(cookies)
	res = chrome.get("https://www.roblox.com/my/groupadmin.aspx?gid=4556091#nav-relationship")
	chrome.browser.find_element_by_id("ctl00_ctl00_cphRoblox_cphMyRobloxContent_AllyNameTextBox").send_keys("Scuf")

	chrome.browser.find_element_by_id("RequestAlly").click()

	# print(chrome.)






if __name__ == '__main__':
	main()