#include <iostream>
#include <string>
using std::string;
using std::cout;

class Family{
public:
	//Default Constructor
	Family();

    //Destructor
	~Family();
    //Copy Constructor
    Family(const Family & rhs);
    //Move Constructor
    Family(Family && rhs);
    //Copy Assignment
    Family & operator=(const Family & rhs);  
    //Move Assignment
    Family & operator=(Family && rhs);
        
    bool addFamilyMember(string newFamilyMember);
    
    void printFamily();
    
private:
    string* m_FamilyMembersArray; 
    int m_NumberOfFamilyMembers;
};


// 1) Put definition a default constructor here
Family::Family()
    : m_FamilyMembersArray(nullptr), m_NumberOfFamilyMembers( 0)
{ }

// 2) Include the definition of the "Big Five" here
//Destructor
Family::~Family(){
	delete [] m_FamilyMembersArray;
	m_FamilyMembersArray = nullptr;
	m_NumberOfFamilyMembers = 0;
}

//Copy Constructor 
Family::Family(const Family & rhs){
	m_FamilyMembersArray = new string[rhs.m_NumberOfFamilyMembers];
	m_FamilyMembersArray = rhs.m_FamilyMembersArray;
	m_NumberOfFamilyMembers = rhs.m_NumberOfFamilyMembers;
}
//Move Constructor
Family::Family(Family && rhs){
	m_FamilyMembersArray = rhs.m_FamilyMembersArray;
	rhs.m_FamilyMembersArray = nullptr;
	m_NumberOfFamilyMembers = rhs.m_NumberOfFamilyMembers;
	rhs.m_NumberOfFamilyMembers = 0;
}

//Copy Assignment
Family & Family::operator= (const Family & rhs){
	if(this != &rhs){
		if(m_FamilyMembersArray == nullptr){
			m_FamilyMembersArray = new string[rhs.m_NumberOfFamilyMembers];
			m_FamilyMembersArray = rhs.m_FamilyMembersArray;
			m_NumberOfFamilyMembers = rhs.m_NumberOfFamilyMembers;
		}
		else{
		*m_FamilyMembersArray = *rhs.m_FamilyMembersArray;
		m_NumberOfFamilyMembers = rhs.m_NumberOfFamilyMembers;
		}
	}
		return *this;
	
}
   
//Move Assignment
Family & Family::operator= (Family && rhs){
	std::swap(m_FamilyMembersArray, rhs.m_FamilyMembersArray);
	std::swap(m_NumberOfFamilyMembers, rhs.m_NumberOfFamilyMembers);
	return *this;
}

bool Family::addFamilyMember(string newFamilyMember){
    string* oldArray = m_FamilyMembersArray;
    m_FamilyMembersArray = new string[++m_NumberOfFamilyMembers];
    for(int i = 0; i < m_NumberOfFamilyMembers - 1; i++){
        m_FamilyMembersArray[i] = std::move( oldArray[i]);
    }
    if( oldArray != nullptr){
        delete [] oldArray;
    }
    m_FamilyMembersArray[m_NumberOfFamilyMembers - 1] = newFamilyMember;
    return true;
}

void Family::printFamily(){
    for(int i = 0; i < m_NumberOfFamilyMembers; i++){
        cout << "Family member index " << i << ": " << m_FamilyMembersArray[i] << "\n";
    }
}

int main(){

    Family happyFamily; // default constructor
    
    happyFamily.addFamilyMember("Mom");
    happyFamily.addFamilyMember("Dad");
    happyFamily.addFamilyMember("Daughter");
    happyFamily.addFamilyMember("Son");

    cout << "Family copyCatFamily( happyFamily );\n";
    Family copyCatFamily( happyFamily ); // copy constructor
    
    cout << "\nPrinting happyFamily...\n";
    happyFamily.printFamily();
    
	cout << "\nPrinting copyCatFamily...\n";
    copyCatFamily.printFamily();
    
    Family jonesFamily;
    cout << "\njonesFamily = happyFamily;\n";
    jonesFamily = happyFamily; // copy assignment operator=

    cout << "\nPrinting happyFamily...\n";
    happyFamily.printFamily();
    
    cout << "\nPrinting jonesFamily...\n";
    jonesFamily.printFamily();
    
    cout << "\nFamily changFamily( std::move( happyFamily));\n";
    Family changFamily( std::move( happyFamily));

    cout << "\nPrinting happyFamily...\n";
    happyFamily.printFamily();
    
    cout << "\nPrinting changFamily...\n";
    changFamily.printFamily();

    Family smithFamily;
    cout << "\nsmithFamily = std::move( copyCatFamily);\n";
    smithFamily = std::move( copyCatFamily);

    cout << "\nPrinting copyCatFamily...\n";
    copyCatFamily.printFamily();

    cout << "\nPrinting smithFamily...\n";
    smithFamily.printFamily();
    
    return 0;
}
