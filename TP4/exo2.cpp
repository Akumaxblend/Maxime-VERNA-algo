#include <time.h>
#include <stdio.h>

#include <QApplication>
#include <QDebug>

#include "tp3.h"
#include "tp4.h"
#include "tp4_exo2.h"
#include "HuffmanNode.h"

_TestMainWindow* w1 = nullptr;
using std::size_t;
using std::string;

void processCharFrequences(string data, Array& frequences);
void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize);
HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode);
HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize);

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree);
string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot);


void main_function(HuffmanNode*& huffmanTree)
{
    string data = "Ouesh, bien ou bien ? Ceci est une chaine de caracteres sans grand interet";

    // this array store each caracter frequences indexed by their ascii code
    Array characterFrequences(256);
    characterFrequences.fill(0);
    // this array store each caracter code indexed by their ascii code
    string characterCodes[256];
    HuffmanHeap priorityMinHeap;
    int heapSize = 0;

    processCharFrequences(data, characterFrequences);
    displayCharacterFrequences(characterFrequences);
    buildHuffmanHeap(characterFrequences, priorityMinHeap, heapSize);
    qDebug() << priorityMinHeap.toString().toStdString().c_str();

    huffmanTree = buildHuffmanTree(priorityMinHeap, heapSize);
    huffmanTree->processCodes("");
    string encoded = huffmanEncode(data, huffmanTree);
    string decoded = huffmanDecode(encoded, *huffmanTree);

    qDebug("Encoded: %s\n", encoded.c_str());
    qDebug("Decoded: %s\n", decoded.c_str());
}


void processCharFrequences(string data, Array& frequences)
{
    /**
      * Fill `frequences` array with each caracter frequence.
      * frequences is an array of 256 int. frequences[i]
      * is the frequence of the caracter with ASCII code i
     **/

    // Your code
    frequences.fill(0);

    for(int i = 0 ; i< data.size() ; i++){

        frequences[(int)(data.at(i))] ++;
    }
}

void HuffmanHeap::insertHeapNode(int heapSize, HuffmanNode* newNode)
{
    /**
      * Insert a HuffmanNode into the lower heap. A min-heap put the lowest value
      * as the first cell, so check the parent should be lower than children.
      * Instead of storing int, the cells of HuffmanHeap store HuffmanNode*.
      * To compare these nodes use their frequences.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/

    // Your code
    int i = heapSize;
	(*this)[i] = newNode;

	while(i > 0 && this->get(i)->frequences < this->get((i-1) / 2)->frequences){

		swap(i, (i-1)/2);

		i = (i-1) / 2;

	}

}

void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize)
{
    /**
      * Do like Heap::buildHeap. Use only non-null frequences
      * Define heapSize as numbers of inserted nodes
      * allocate a HuffmanNode with `new`
     **/

    // Your code
    heapSize = 0;

    for(int i = 0 ; i < frequences.size() ; i++){

		if(frequences[i] != 0){

            HuffmanNode * toInsert = new HuffmanNode;
            toInsert->character = (char)i;
            toInsert->frequences = frequences[i];

            priorityMinHeap.insertHeapNode(heapSize, toInsert);
            heapSize++;
        }
	}

    

}

void HuffmanHeap::heapify(int heapSize, int nodeIndex)
{
    /**
      * Repair the heap starting from nodeIndex. this is a min-heap,
      * so check the parent should be lower than children.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/
    // Your code

    int i_max = nodeIndex;

	if((nodeIndex * 2) + 1 < heapSize){

		if(this->get((nodeIndex * 2) + 1) < this->get(i_max)){

			i_max = (nodeIndex * 2) + 1;
	}
	

	}if((nodeIndex * 2) + 2 < heapSize){

		if (this->get((nodeIndex * 2) + 2) < this->get(i_max)){

			i_max = (nodeIndex * 2) + 2;
		}
	}	

	if(i_max != nodeIndex){

		this->swap(i_max, nodeIndex);

        // HuffmanNode* tmp = this->get(nodeIndex);
		// (*this)[nodeIndex] = (*this)[i_max];
		// (*this)[i_max] = tmp;

		heapify(heapSize, i_max);
	}
	else return;

}


HuffmanNode* HuffmanHeap::extractMinNode(int heapSize)
{
    /**
      * Extract the first cell, replace the first cell with the last one and
      * heapify the heap to get a new well-formed heap without the returned cell
      * you can use `this->swap`
     **/

    // Your code

    HuffmanNode * toReturn = new HuffmanNode;

    toReturn->character = this->get(0)->character;
    toReturn->frequences = this->get(0)->frequences;

    this->swap(0, heapSize-1);

    this->heapify(heapSize - 1, 0);


    return toReturn;
}

HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode)
{
    /**
     * Make a subtree (parent + 2 children) with the given 2 nodes.
     * These 2 characters will be the children of a new parent node which character is '\0'
     * and frequence is the sum of the 2 children frequences
     * Return the new HuffmanNode* parent
     **/
    // Your code

    HuffmanNode * parent = new HuffmanNode('\0');

    parent->left = leftNode;
    parent->right = rightNode;

    parent->frequences = leftNode->frequences + rightNode->frequences;

    return parent;
}

HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize)
{
    /**
      * Build Huffman Tree from the priorityMinHeap, pick nodes from the heap until having
      * one node in the heap. For every 2 min nodes, create a subtree and put the new parent
      * into the heap. The last node of the heap is the HuffmanTree;
      * use extractMinNode()
     **/

    // Your code

    HuffmanNode* node1 = new HuffmanNode;
    HuffmanNode* node2 = new HuffmanNode;
    HuffmanNode* parent = new HuffmanNode;
    
    while (heapSize > 1){

        

        node1 = priorityMinHeap.extractMinNode(heapSize);
        heapSize--;
        node2 = priorityMinHeap.extractMinNode(heapSize);
        heapSize--;

        parent = makeHuffmanSubTree(node1, node2);

        priorityMinHeap.insertHeapNode(heapSize, parent);
        heapSize ++;
        
        
    }
    
    //HuffmanNode* toReturn = new HuffmanNode('?');
    HuffmanNode* toReturn = priorityMinHeap.extractMinNode(heapSize);


    return toReturn;
}

void HuffmanNode::processCodes(const std::string& baseCode)
{
    /**
      * Travel whole tree of HuffmanNode to determine the code of each
      * leaf/character.
      * Each time you call the left child, add '0' to the baseCode
      * and each time call the right child, add '1'.
      * If the node is a leaf, it takes the baseCode.
     **/

    // Your code
    std::string newCode = baseCode;

    while(!(this->isLeaf())){

        if(this->left){

            newCode += "0";
            this->left->processCodes((const string&)newCode);
        }

        else if(this->right){

            newCode += "1";
            this->right->processCodes((const string&)newCode);
        }
    }
    this->code = baseCode;
    return;
    
}

void HuffmanNode::fillCharactersArray(std::string charactersCodes[])
{
    /**
      * Fill the string array with all nodes codes of the tree
      * It store a node into the cell corresponding to its ascii code
      * For example: the node describing 'O' should be at index 79
     **/
    if (!this->left && !this->right)
        charactersCodes[this->character] = this->code;
    else {
        if (this->left)
            this->left->fillCharactersArray(charactersCodes);
        if (this->right)
            this->right->fillCharactersArray(charactersCodes);
    }
}

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree)
{
    /**
      * Encode a string by using the huffman compression.
      * With the huffmanTree, determine the code for each character
     **/

    // Your code
    std::string charactersCodes[256]; // array of 256 huffman codes for each character
    huffmanTree->fillCharactersArray(charactersCodes);
    string encoded = "";


    for(int i = 0; i < toEncode.size(); i++){

        encoded += charactersCodes[toEncode.at(i)];
        
    }


    return encoded;
}


string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot)
{
    /**
      * Use each caracters of toDecode, which is '0' either '1',
      * to travel the Huffman tree. Each time you get a leaf, get
      * the decoded character of this node.
     **/
    // Your code
    string decoded = "";

    //HuffmanNode target = huffmanTreeRoot;

    for(int i = 0 ; i <toDecode.size() ; i++){

        if(toDecode.at(i) == 0){

            target = target.left;

        }

        else{

            target = target.right;
        }

        if(target.isLeaf()){

            decoded += target.character;
            target = huffmanTreeRoot;
        }
    }

    return decoded;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Array::wait_for_operations = false;
    w1 = new HuffmanMainWindow(main_function);
    w1->show();
    return a.exec();
}
