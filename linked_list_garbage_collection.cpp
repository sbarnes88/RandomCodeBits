#include <iostream>
#include <list>
#include <sstream>
#include <string>

#define null NULL

class object {
private:
    char* hash;
public:
    object() {
        std::ostringstream get_the_address;
        get_the_address << this;
        std::string strhash = get_the_address.str();
        hash = new char[strhash.size() +1];
        std::copy(strhash.begin(), strhash.end(), hash);
        hash[strhash.size()] = '\0';
    }
    
    char* getHash() {
        return hash;
    }
};

class LinkedList {
public:
    char chars[4096];
    object* value;
    LinkedList* next;
    LinkedList* prev;
    LinkedList* last;
    
    LinkedList() {
        next = NULL;
        prev = NULL;
    }
    
    void setValue(object* val) {
        if(value != null) {
            delete value;
        }
        value = val;
    }
    
    void remove() {
        if(next != NULL && prev != null) {
            LinkedList* tmp = next;
            prev->next = next;
            next->prev = tmp->prev;
            delete tmp;
        }
    }
    
    void addToEnd(object* val) {
        int iterations = 0;
        LinkedList* nextValue = this->next;
        if(next == null) {
            nextValue = new LinkedList();
            nextValue->value = val;
            nextValue->prev = this;
            next = nextValue;
            last = next;
        }else {
            if(last != NULL)
                next = last;
            LinkedList* tmp = new LinkedList();
            while(nextValue->next != NULL) {
                nextValue = nextValue->next;
                iterations++;
            }
            tmp->value = val;
            tmp->next = NULL;
            tmp->prev = nextValue;
            nextValue->next = tmp;
            last = tmp;
        }
        
        //std::cout << "Added after " << iterations << " iterations." << std::endl;
    }
    
    void removeAll() {
        int count = 0;
        LinkedList* lastNode = next;
        while(lastNode->next != null) {
            lastNode = lastNode->next;
        }
        LinkedList* currentNode = lastNode;
        while(lastNode->prev != null) {
            //std::cout << lastNode->value->getHash() << std::endl;
            delete lastNode->value;
            currentNode = lastNode;
            lastNode = lastNode->prev;
            delete currentNode;
            count++;
        }
        //std::cout << lastNode->value->getHash() << std::endl;
        delete lastNode->value;
        delete lastNode;
        count++;
        
        std::cout << "Deleted " << count << " objects." << std::endl;
    }
};

std::list<object*> gc;

class Test : public object {
	public:
        Test() {
            //std::cout << getHash() << std::endl;
        }
		void Run() {
			std::cout << "Hello World" << std::endl;
		}
};

void runGarbageCollection() {
    std::cout << "Collection contains: " << gc.size() << " items to release" << std::endl;
    for(object* i : gc) {
        delete i;
    }
}

int main() {
	Test* t = new Test();
	gc.push_front(t);
    t->Run();
    
    LinkedList* ll = new LinkedList();
    ll->value = t;
    
    for(int x = 0; x < 1024*1024; x++) {
        ll->addToEnd(new Test());
    }
    
    
    ll->removeAll();
    //runGarbageCollection();
	return 0;
}
