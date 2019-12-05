
from HuffmanHelper.tree import *
import heapq
import json


class HuffmanEncoder:

	def __init__(self, content):
		self.content = content

	def compress(self, outfile):
		frequency = calculate_frequency(self.content)
		encoding, recovery_dict = create_encoding(frequency, self.content)

		self.write_recovery_dict(recovery_dict, outfile)
		self.write_binary_encoding(encoding, outfile)

		return encoding, recovery_dict

	def write_recovery_dict(self, recovery_dict, outfile):
		with open(outfile, 'w') as w:
			string_recovery_file = json.dumps(recovery_dict)
			w.write(str(len(string_recovery_file)))
			w.write("|")
			w.write(string_recovery_file)

	def write_binary_encoding(self, huffmanEncodedString, outfile):
		leftover_bits = len(huffmanEncodedString) % 8

		with open(outfile, 'ab+') as binary_file:
			if leftover_bits != 0:
				huffmanEncodedString += '0' * (8 - leftover_bits)

			# Create a bytearray to store all of the bits into a file.
			byte = bytearray(int(huffmanEncodedString[i:i + 8], 2) for i in range(0, len(huffmanEncodedString), 8))
			binary_file.write(byte)

		return

def create_mapping(heap_node):
    codebook = {}
    code = traverse_tree(heap_node, '')
    
    for key, value in code:
        codebook.update({key: value})

    return codebook



def create_encoding(freq_dict, inputfile):

    count = 0
    min_heap = []
    # add each elemet to heap
    for key, value in freq_dict.items():
        heapq.heappush(min_heap, (value, (count, key)))
        count += 1


    # merge all nodes until there is only 1 root node left and all other nodes will be child to it
    while len(min_heap) > 1:
        count += 1
        node_1 = heapq.heappop(min_heap)
        node_2 = heapq.heappop(min_heap)

        parent_node = node_1[0] + node_2[0]

        if node_1[0] <= node_2[0]:
            tree_data = Tree(parent_node, node_1, node_2)
        else:
            tree_data = Tree(parent_node, node_2, node_1)
        heapq.heappush(min_heap, (parent_node, (count, tree_data)))

    # if all nodes are merged, create a mapping for each character
    if len(min_heap) == 1:
        character_mapping = create_mapping(heapq.heappop(min_heap))

    inputString = list(inputfile) # convert user input file to list

    # convert every character in inputString to correspoing huffman encoded text
    for i in range( len(inputString) ):
        inputString[i] = character_mapping[inputString[i]]

    inputString = ''.join(inputString) # create a huffman encoded string
    flipped_character_mapping = dict(zip(character_mapping.values(), character_mapping.keys())) # reverse huffman helper 
    flipped_character_mapping.update({'length': len(inputString)}) # add length to dict

    return inputString, flipped_character_mapping


def calculate_frequency(inputfile):
    # Takes in a read file and creates a key, value dict.
    # Key denotes the character and value denotes the frequency.
    frequency_dict = {}

    # Iterate character by character and check if found within dict.
    for character in inputfile:
        if character in frequency_dict:
            # Chacter found increment frequency.
            frequency_dict[character] += 1
        else:
            # Character not found create key with value 1.
            frequency_dict.update({character: 1})

    return frequency_dict

