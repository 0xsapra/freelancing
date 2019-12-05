import sys
import os

from arithmeticCompress import *
from arithmeticDecompress import *

from huffmanDecompress import HuffmanDecoder
from huffmanCompress import HuffmanEncoder

from ArithmeticHelper.BitStream import InputStream, OutputStream

def encode_arithmetic(inputFile, outfile):

	print(f'Uncompressed\t>> InputFile size:\t{os.stat(inputFile).st_size} bytes')
	precision = 32 # Integer specifying number of bits in 1 character. so 16 means 1 character = 16 bits which is also called UTF-16

	with open(inputFile, "rb") as inp, open(outfile, "wb") as out :
		# create a output stream to write compressed data onto
		# call compress function to read Input to compress, compress it and write to output file
		# close the output stream
		outStream = OutputStream(out, precision)
		compress(inp.read(), outStream) 
		outStream.close()

	print(f'Compressed\t>> OutputFile size:\t{os.stat(outfile).st_size} bytes')

def decode_arithmetic(inputFile, outfile):

	print(f'Compressed\t>> InputFile size:\t{os.stat(inputFile).st_size} bytes')
	precision = 32 # Integer specifying number of bits in 1 character. so 16 means 1 character = 16 bits which is also called UTF-16

	with open(outfile, "wb") as out, open(inputFile, "rb") as inp:
		# create a input stream to read compressed bytes from
		# read frequency table stored in compressed file
		# read the data in compressed file and use frequency table to uncompress data
		bitin = InputStream(inp, precision)
		freqs = read_frequencies(bitin)
		decompress(freqs, bitin, out)

	print(f'Uncompressed\t>> OutputFile size:\t{os.stat(outfile).st_size} bytes')

def encode_huffman(inputFile, outfile):
	
	# read the content to compress from input file
	with open(inputFile, 'r') as inp:
		content = inp.read()

	print(f'Uncompressed\t>> InputFile size:\t{os.stat(inputFile).st_size} bytes')

	encoding, recovery_dict = HuffmanEncoder(content).compress(outfile) # compress the content


	print(f'Compressed\t>> OutputFile size:\t{os.stat(outfile).st_size} bytes')
	
	return
		

def decode_huffman(inputFile, outfile):

	# read the content of compressed binary file 
	print(f'Compressed\t>> InputFile size:\t{os.stat(inputFile).st_size} bytes')

	decoded_content = HuffmanDecoder().decompress(inputFile, outfile) # uncompress the content

	# write the uncompressed data onto out file

	print(f'Uncompressed\t>> OutputFile size:\t{os.stat(outfile).st_size} bytes')

def main():
	if len(sys.argv) > 1:
		compressionFile = sys.argv[1]
		newFileName = compressionFile.split(".")[0]

		outArithmeticCompressedFile = f"{compressionFile}.arthmetic.bin"
		outArithmeticDecompressedFile = f"{newFileName}.arthmetic.txt"

		outHuffmanCompressedFile = f"{compressionFile}.huffman.bin"
		outHuffmanDecompressedFile = f"{newFileName}.huffman.txt"

		print("............................")
		print("Statistics Arithmetic Coding")
		print("............................")
		# encode_arithmetic(compressionFile, outArithmeticCompressedFile) #5afc
		# decode_arithmetic(outArithmeticCompressedFile, outArithmeticDecompressedFile)
		print("............................")
		print("Huffman Coding")
		print("............................")
		encode_huffman(compressionFile, outHuffmanCompressedFile)
		decode_huffman(outHuffmanCompressedFile, outHuffmanDecompressedFile)

	else:
		print("[-]Usage python3 main.py fileToCompress")
		sys.exit(1)


if __name__ == '__main__':
	main()







