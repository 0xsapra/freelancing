class RuntimeException : public std::exception {
	
public:
	std::string m_error;

	RuntimeException(std::string error){
		m_error = error;
	}

	virtual const char *what() const noexcept override { return m_error.c_str(); }
};

class LinkedException : public RuntimeException {
public:
	LinkedException(const std::string& err) : RuntimeException(err) {}
};


template<typename T>
class SNode{
public:
	T data;
	SNode* next;

	SNode(T t){
		this->data = t;
		this->next = NULL;
	}

};



template <typename E>
class SLinkedList { 		// a singly linked list
public:
	SLinkedList(){ // list constructor
		this->head = NULL;
		this->tail = NULL;
	} 			
	~SLinkedList(){ // destructor

	}
	
	bool empty() const{  	// is list empty? Returns true or false
		if(this->head == NULL){
			return true;
		} else {
			return false;
		}
	}
	const E& front() const{  // returns front element
		if(!this->empty()){
			return this->head->data;
		} 
		throw LinkedException("The list is empty");


	}
	const E& last() const{ // return last element
		SNode<E>* temp = this->head;
		if(!this->empty()){
			return this->tail->data;
		}
		throw LinkedException("The list is empty");
	}
	void addFront(const E& e){ // add e to front of list
		
		SNode<E>* temp = this->head;
		SNode<E>* newNode = new SNode<E>(e);

		if( this->empty() ){
			this->head = newNode;
			this->tail = newNode;
		} else {
			newNode->next = this->head;
			this->head = newNode;
		}
		
		return;


	}
	void addLast(const E& e){ // add e to rear of list
		SNode<E>* temp = this->tail;
		SNode<E>* newNode = new SNode<E>(e);

		if(this->empty()){
			this->head = newNode;
			this->tail = newNode;
		} else {

			this->tail = newNode;
			temp->next = newNode;
		}
		return;
		
	}
	void removeFront(){ // remove the front element from list
		
		if(this->empty()){
			throw LinkedException("Cannot delete from empty List");
		} else {
			SNode<E>* temp = this->head;	
			this->head = this->head->next;
			delete temp;
		}
		return;

	}
	void removeLast(){ // remove the last element from list
		if(this->empty()){
			throw LinkedException("Cannot delete from empty List");
		} else {
			SNode<E>* temp = this->head;
			SNode<E>* temp2;
			if(temp->next == NULL){ // this is 1 and only value in list, so just remove it
				temp2 = temp;
				this->head = NULL;
				delete temp;
			} else {
				while(temp->next->next != NULL){
					temp = temp->next;
				}
				temp2 = temp->next;
				temp->next = NULL;
				delete temp2;
			}
		}
		return;
		

	}
	void print(){ // print the list
		SNode<E>* temp = this->head;
		while(temp){
			std::cout << "Data -> " << temp->data << std::endl;
			temp = temp->next;
		}
		return;
	}
private:
	SNode<E>* head; // head of the list - a pointer to the first node
	SNode<E>* tail; // tail of the list - apointer to the last node
};
