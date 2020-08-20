/* Prog3Vigenere.cpp
 *     Encode/Decode using Vigenere cipher.
 */

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cctype>     // Allows using the tolower() function
#include <cstring>
using namespace std;
// Global constants
const int MaxWordSize=81; //biggest word
const int total=21735; //total words in dictionary.txt
const int minimumSize=3; //word cannot be shorter than 3 letters


void openDictionary(char str[total][MaxWordSize]) //opening the dictionary file!
{
  ifstream IF;
  char cWord[MaxWordSize]; //the current word
  int rownum=0; //the row number for the current word
  IF.open("dictionary.txt");
  if( !IF.is_open()) //if the dictionary file isn't found
  {
    cout<<"Could not find dictionary.txt. Exiting..."<<endl;
    exit(-1);
  }
  while(IF>>cWord)
  {
    if(strlen(cWord)>=minimumSize)
    {
        for(int i=0;i<strlen(cWord);i++)
        {
          cWord[i]=tolower(cWord[i]); //converting to lower case
        }
        strcpy(str[rownum],cWord);
        rownum++;
    }
  }
  IF.close();
}


bool LookupTheWord(char dictionary[total][MaxWordSize],char theWord[])
{
   int high=total-1;
   int mid;
   int low = 0;

   while(low <= high)                                   // if your high greater than low.
   {
      mid = (low + high)/ 2.0;

         if(strcmp(dictionary[mid], theWord) == 0)      // compare the word form the dictioanry
         {
           return true;                                 // if you found the word than return true.
         }
         else if(strcmp(dictionary[mid], theWord) < 0)
         {
            low = mid +1;                               // if the word not found in the below half part
         }                                              // than your midpoint is high
         else
            high = mid -1;                              // else high is mid -1.
   }

    return false;
}

void textEncoder(char str1[], char str2[]) //ENCODING FUNCTION
{
  int x= strlen(str1);
  char encodedStr[MaxWordSize];
  char key[x];
  for(int i=0;i<x-1;i++)
  {
    key[i]=str1[i];
  }
  int k=0,i;
  for(i=0;i<x && k<strlen(str2);i++) //MAKING PLAINTEXT IN TERMS OF KEYWORD
  {
    key[i]=str2[k];
    k++;
    if(k==strlen(str2))
      k=0;
    key[i]=tolower(key[i]);
  }
  key[i]='\0';
  for(i=0;i<strlen(str1);i++) //TO CIPHER THE TEXT
  {
    if(isalpha(str1[i])) //CHECK IF ELEMENT IS ALPHABET
    {
      str1[i]=tolower(str1[i]); //CONVERT TO LOWER CASE
      str1[i]-='a';
      key[i]-='a';
      char h= (str1[i]+key[i])%26;
      h+='A';
      h=tolower(h);
      encodedStr[i]=h;
      str1[i]+='a';
      key[i]+='a';
    }
    else if(str1[i]==' ')
    {
      char h=' ';
      encodedStr[i]=h;
    }
  }
  encodedStr[i]='\0';
  cout<<key<<endl;
  cout<<str1;
  cout<<encodedStr<<endl;
}


int textDecoder(char str1[], char str2[],
  char decodedStr[]) //DECODE TEXT
{
  int ctr=0;
  int x= strlen(str1);
  char key[x];
  for(int i=0;i<x;i++)
  {
    key[i]=str1[i];
  }
  int k=0,i;
  for(i=0;i<x&&k<strlen(str2);i++) //MAKING PLAINTEXT IN TERMS OF KEYWORD
  {
    key[i]=str2[k];
    k++;
    if(k==strlen(str2))
      k=0;
    key[i]=tolower(key[i]);
  }
  key[i]='\0';
  for(i=0;i<x;i++)
  {
    if(isalpha(str1[i]))
    {
      str1[i]=tolower(str1[i]);
      str1[i]-='a';
      key[i]-='a';
      char h=(str1[i]-key[i]+26)%26;
      h+='A';
      h=tolower(h);
      decodedStr[i]=h;
      str1[i]+='a';
      key[i]+='a';
    }
    else
    {
      char h= str1[i];
      decodedStr[i]=h;
    }
  }
  decodedStr[i]='\0';
  return 0;
}

void bookReader(char str1[], char str2[total][MaxWordSize])
{
  char str3[MaxWordSize];
   char tempWord[81];
   int start = 0;
   int counter = 0;
   int max = 0;
   ifstream IF;
   int currentRow = 0;
   IF.open( "TheSecretAgentByJosephConrad.txt");
   if( !IF.is_open())
   {
      cout << "Could not find TheSecretAgentByJosephConrad.txt.  Exiting..." << endl;
      exit( -1);
   }
   char theWord[MaxWordSize];
   start =0;
   counter =0;
   while( IF >> theWord)
   {
      counter = 0;                                         // initial condition of counter
      start = 0;                                           // initial condition of start

      if (strlen(theWord) >=  minimumSize)                 // word size greater than 3
      {
        for(int i=0;i<strlen(theWord);i++)
          theWord[i]=tolower(theWord[i]);
         textDecoder(str1,theWord,str3);  // call encript function

         int oldEnd = strlen(str3);
         str3[oldEnd] = ' ';                          // replaceing space to null charecter
         str3[oldEnd + 1] = '\0';

         int i =0;

         for(i=0; i<strlen(str3); i++)                      // find the length of the plain text
         {
               if (str3[i] == ' ')
               {                        // When you get space copy the first word copy the word
                     strncpy(tempWord, str3 + start, i-start);
                     tempWord[i-start] = '\0';                   // make temperary

                     // call lookup function, if word found in dictionary then increase counter
                     if( LookupTheWord(str2,tempWord) == true)
                     {
                        counter++;

                     }
                     start = i+1;
               }


            }

         str3[strlen(str3) -1 ] = '\0';

         if(counter > max)                                      //  if counter is greater than max
         {
            cout << counter << " words found using keyword: "<< theWord << " giving:" << endl;
            cout << "   " << str3 << endl;
            max = counter;
         }
      }
   }

    // close the file
    IF.close();
}

//---------------------------------------------------------------------------
int main()
{
    // Declare variables
    char wordSearch[MaxWordSize];
    int menuOption;                   // Userinput for menu option
    char returnCharacter;             // Separately store the return character so cin.getline does not consider it the next user input
    char wordToEncode[MaxWordSize], keyword[MaxWordSize];
    char cipherText[MaxWordSize];
    char plainText[MaxWordSize];
    char dictionary[total][MaxWordSize];
    char tempWord[MaxWordSize];
    openDictionary(dictionary);
    // Display menu and handle menu options

    cout<<"21735 words of size >= 3 were read in from dictionary. "<<endl<<endl;
    cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
        cin >> menuOption;
        returnCharacter = cin.get();  // Read and discard the return character at the end of the above input line.
                                      // This is necessary because otherwise a subsequent cin.getline() reads it as
                                      // an empty line of input.
    switch( menuOption)
    {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
            cout << "Enter a word to be looked up in dictionary: ";
            cin>>wordSearch;
            LookupTheWord(dictionary, wordSearch);
            if(LookupTheWord(dictionary, wordSearch)==true)
              cout<<wordSearch<<" IS in the dictionary."<<endl;
            else
              cout<<wordSearch<<" is NOT in the dictionary."<<endl;
            break;

        case 2: // Encode some text
            cout << "Enter the text to be encoded: ";
            fgets(wordToEncode,MaxWordSize,stdin);
            cout<<"Enter a keyword for Vinegere encryption: ";
            cin>>keyword;
            cout << "Keyword, plainText and ciphertext are:  \n";
            textEncoder(wordToEncode,keyword);
            break;

        case 3:{ // Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            fgets(cipherText, MaxWordSize,stdin);
            cout << "Enter a Vigenere keyword to be tried: ";
            cin>>keyword;
            textDecoder(cipherText,keyword,plainText);
            int start = 0;
            int counter = 0;
            for(int i=0; i<strlen(plainText) + 1; i++)
            {
               if (plainText[i] == ' ' || plainText[i] == '\0')
               {
                strncpy(tempWord, plainText + start, i-start);    // When you get space copy the first word
                    tempWord[i-start] = '\0';
                    if( LookupTheWord(dictionary,tempWord) == true)
                    {
                        counter++;
                    }
                    start = i+1;
                }
            }
            cout << counter << " words found using keyword: "<< keyword << " giving:" << endl;
            cout << "   " << plainText << endl;
          break;}
        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";
            fgets(cipherText, MaxWordSize,stdin);
            bookReader(cipherText, dictionary);
            break;

        case 5: // exit program
            cout << "Exiting program" << endl;
            exit( 0);
            break;

        default:
            // Sanity check
            cout << "Invalid menu option.  Exiting program." << endl;
            break;
    }// end switch( menuOption)

    return 0;
}//end main()
