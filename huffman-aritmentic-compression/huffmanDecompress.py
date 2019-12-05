
from HuffmanHelper.tree import *
import json

class HuffmanDecoder:
    

    def __init__(self):
        pass

    def decompress(self, infile, outfile):
        self.inputstream = open(infile, 'rb')

        self.recovery_dict = self.read_recovery_dict()
        encoded_huffman = self.inputstream.read() # read the rest of code

        decoded_str = self.decode_file(self.recovery_dict, encoded_huffman)
        with open(outfile, 'w') as f:
            f.write(decoded_str)



    # read the stored huffman mapping from compressed file
    def read_recovery_dict(self):

        length = self.read_length()
        recovery_dict = ''
        for i in range(length):
            read_bit = self.inputstream.read(1).decode('utf-8')
            recovery_dict += read_bit

        recovery_dict = json.loads(recovery_dict)
        return recovery_dict


    # decode compressed data using huffman recovery dict
    def decode_file(self, recovery_dict, huffman_code):
        symbol, decoded_file, bit_string = "", "", ""
        for byte in huffman_code:
            bit_string += format(byte, '08b')

        for i in range(0, recovery_dict['length']):
            symbol += bit_string[i]
            if symbol in recovery_dict:
                decoded_file += recovery_dict[symbol]
                symbol = ""
        return decoded_file

    # read the length of recovery dict which is 1st n bytes of compressed file until | is found
    def read_length(self):
        int_val = ''
        while 1:
            readByte = self.inputstream.read(1).decode('utf-8')
            if readByte == "|":
                break
            int_val += readByte
        return int(int_val)
