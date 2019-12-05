class Tree():
    # Class Tree is used to create the huffman tree which will be traversed.
    def __init__(self, parent, left_child=None, right_child=None):
        self.parent = parent
        self.left_child = left_child
        self.right_child = right_child



def traverse_tree(heap_node, char):
    # in order traversal algo for tree

    if isinstance(heap_node[1][1], Tree):
        left = traverse_tree(heap_node[1][1].left_child, char + '0')
        right = traverse_tree(heap_node[1][1].right_child, char + '1')

        return left + right
    else:
        # exit condition
        # found a leaf node
        char = [(heap_node[1][1], char)]
        return char

