import json


def get_cookies():

	cookie_dict = {
		"domain" : "",
		"name"   : "",
		"value"	 : ""
	}
	with open("cookie.json", "r") as f:
		unparsed_cookie = f.read()
	
	parsed_cookie = json.loads(unparsed_cookie)

	for key in cookie_dict:
		if not key in parsed_cookie:
			raise Exception(f"Required name {key} is missing in cookie.json")

		if parsed_cookie[key] == "":
			raise Exception(f"Required name {key} is missing in cookie.json")

		
		cookie_dict[key] = parsed_cookie[key]

	return cookie_dict
