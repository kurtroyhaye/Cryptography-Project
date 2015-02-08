# include <stdlib.h>
# include <ctype.h>
# include <conio.h>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <map>
//Just added.
using namespace std;




//Compression and Depression for sub menu
template <typename Iterator>
Iterator compress(const std::string &uncompressed, Iterator result) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<std::string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[std::string(1, i)] = i;
 
  std::string w;
  for (std::string::const_iterator it = uncompressed.begin();
       it != uncompressed.end(); ++it) {
    char c = *it;
    std::string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
      *result++ = dictionary[w];
      // Add wc to the dictionary.
      dictionary[wc] = dictSize++;
      w = std::string(1, c);
    }
  }
 
  // Output the code for w.
  if (!w.empty())
    *result++ = dictionary[w];
  return result;
}
 
// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
std::string decompress(Iterator begin, Iterator end) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<int,std::string> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[i] = std::string(1, i);
 
  std::string w(1, *begin++);
  std::string result = w;
  std::string entry;
  for ( ; begin != end; begin++) {
    int k = *begin;
    if (dictionary.count(k))
      entry = dictionary[k];
    else if (k == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed k";
 
    result += entry;
 
    // Add w+entry[0] to the dictionary.
    dictionary[dictSize++] = w + entry[0];
 
    w = entry;
  }
  return result;
}
//Compression & Decompression codes end here.




int main()
{
	
	
	
int select;

bool menu = true;
while (menu != false)
	{
		cout << "==============================\n";
		cout << "* 1 - Open File.             *\n";
		cout << "* 2 - Process File.          *\n";
		cout << "* 3 - Exit.                  *\n";
		cout << "==============================\n";	
		cout << "Enter your choice and press enter:\n";

		cin >> select;

		switch (select)
		{
	case 1:
		{	
			string filename;
			ifstream inData;  //For reading of text file.
			string text;

	
			cout << "=============Open File============\n";
			cout << "Enter the data file name : \n" << endl;
			cin >> filename; //Name input of text file.

			//Code to open and view retrieved textfile.
			inData.open(filename.c_str()); // Point where file is opened.
			if (inData.is_open())
			{
				while (!inData.eof())
					{
						getline(inData, text);
						cout << text << endl;
						cout << "\n";
					}
					inData.close();
			}
			else
			{
				cout << "Unable to open file, try again \n";
				break;
			}

			//Code to get current date.
			time_t t = time(NULL);
			tm* timePtr = localtime(&t);

			//Code to copy from text file and create another file with student info.

			string newName;
			cout << "===============New File============\n";
			cout << "Enter name for new Text File: eg name.txt \n"<< endl; 
			cin >> newName; // Name input for new text file.

			//code which copies and create a new text file.

			std:: ofstream f2 (newName.c_str()); //Outputs file
			std:: ifstream f1 (filename.c_str());//Opens and takes files as input.
			string line;

			f2 << "Id: 620044336 " << endl;
			f2 << "\n";
			f2 << "Date: " << (timePtr->tm_mday)<<"/"<< (timePtr->tm_mon)+1 <<"/"<< (timePtr->tm_year)+1900<<endl;
			f2 << "Time: " << (timePtr->tm_hour)<<":"<< (timePtr->tm_min)<<":"<< (timePtr->tm_sec) << endl;
			f2 << "**********************************************************";
			f2 << "\n";

			while(std:: getline(f1, line))
				{
					f2<< line<< endl;
				}
				break;
		}//end of case 1

	case 2: //submenu starts here
	{
		int select;
		bool menu1 = true;

		while (menu1 != false)
		{
			cout << "====================================\n";
			cout << "* 1 - Encrypt File.                *\n";
			cout << "* 2 - Decrypt File.                *\n";
			cout << "* 3 - Compress & Decompress File.  *\n";
	 		cout << "* 4 - Exit.                        *\n";
			cout << "====================================\n\n";	
			cout << "Enter your choice and press enter:";

			cin >> select;
			switch (select)
												//start of switch statement.
		{
case 1: //start of case 1.2
	{
	// Encryption && Decryption code XOR method.	
	
	string convert;
	cout << "==============Encryption===============\n";
	cout << "Enter file to be Encrypted \n" << endl;
	cin >> convert;	

	std:: ifstream encrypt (convert.c_str());

	
	if(encrypt.is_open())
	{
	string text;

	//std::string original;
	std::string encrypted;	

	char key = 'C';
	while(std::getline(encrypt,text)) // !encrypt.eof()
	{
	//std::getline(encrypt,text);
	for (int i = 0; i<text.length();i++)
		{
			
		encrypted += text[i]^key;
		std::ofstream newfile (convert.c_str());//Rewrite same file.
	    newfile << encrypted <<endl<<"\n";
		}	
	}

	}
	else
	{
		cout << "Unable to open file, try again.\n";
	}

	encrypt.close();
	break;	
	}//end of case 1.2	

case 2: //start of case 2.2
	{
		string text;
		string word;
		cout << "==============DECRYPTON============== \n";
		cout << "Enter name of file to be decrypted: \n";
		cin >> text;
		
		std:: ifstream decrypt (text.c_str());
		
		if(decrypt.is_open())
		{
			string name;
			//std::string original;
			std::string decrypted;
			char key = 'C';
			
			cout << "Name of file to store decrypted data.\n";
			cin >> word;
			
			while (!decrypt.eof())
			{
				std:: getline(decrypt, name);
				for(int i = 0; i<name.length(); i++)
				{
					decrypted += name[i]^key;
					std::ofstream outfile (word.c_str(),ofstream::out);//create new file.
	    			outfile << decrypted <<"\n";
				}
				
			}
			
		}
		else
		{
			cout << "Unable to open file, try again.";
		}
	
	decrypt.close();
	break;	
	} // end of case 2.2

case 3: //start of case 3.2
{
	// Text File Compress method....	
	
	string convert;
	string input;
	
	cout << "================COMPRESS_&&_DECOMPRESS==============\n\n";
	cout << "Enter file to be Compressed and Decompressed \n" << endl;
	cin >> convert;	
	cout << "\n\n";
	cout << "Enter new file name to store decompressed data \n";
	cin >> input;

	//Experiment codes start here...	
	string hold;
	ifstream in_file;
	
	in_file.open(convert.c_str(),ios::in);
	
	if(in_file.is_open())
	{
			
		while(getline(in_file,hold))
		{				
			//Save back to same destination.
  			std::ofstream out_file("test.txt",ofstream::out|ofstream::app); // remember must save to same file.
			  		
			std:: vector<int> compressed;
			compress(hold,std::back_inserter(compressed));
			
		
			std:: stringstream ss;
						
	  		std::copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(ss, ","));
			std::cout <<ss.str()<<std::endl;//just added
			out_file << ss.str() << std::endl; //just added
			cout << out_file << endl; //just added
			std::string decompressed = decompress(compressed.begin(), compressed.end());
			//Store decompressed data in new text file....
			std::ofstream d_press (input.c_str(),ofstream::out | ofstream::app);
			d_press << decompressed << "\n ";
			
			
			
			//get size of file
			//ifstream file1("sick.txt",ios::binary | ios::ate);
			//cout << "File Size: "<< file1.tellg()<<endl;
			
			
  			//std::cout << decompressed << std::endl;
  			
  			//out_file <<endl;
  			//out_file<< decompressed <<std::endl;			
	  
		}
		in_file.close();
	}
	else
		{
			cout << "Unable to open file, try again \n";
			break;
		}
			
//Experiment codes end here	
break;
}//end of case 3.2	


case 4:
	{
		goto loop;
		break;
	}
	
} // end of switch statement
	
}// end of while loop for submenu
loop:;

}//end of case 2 first one// submenu ends here.

//case 3 from first menu goes here.
case 3:
{
 exit(0);	
}	
break;
}// end of switch statment

	
}//end of while loop first one.


return 0;
}	
