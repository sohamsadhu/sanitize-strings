/* Assignment 2 for Secure Coding.
 * Author: Soham Sadhu.
 * Sanitizing String Homework. Take in credentials and print them in following format:
 * Name: 					   First_Name Last_Name
 * Credit Card Number:	       XXXX-XXXX-XXXX-XXXX
 * Expiration month and year:  Month name followed by year
 * Security or CVV code:       XXX
 * Zip code:                   XXXXX
 * Purchase amount:            XXX,XXX.XX
 * Email address:              Standard name form@ XXX.XXX
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>			// C99 standard that allows me to declare a bool type variable.

// Referred the tutorial at www.cprogramming.com/tutorial/c/lesson9.html, http://tek-tips.com/viewthread.cfm?qid=1471051&page=6
void getData( char* name, int length )
{
	fgets( name, length, stdin ) ;
	int i = 0 ;
	for( i = 0 ; i < length ; i++ )		// Using the postfix i++ instead of prefix saves me from missing the last one. Even with only a < than operator. 
	{
		if( name[i] == '\n' || i == ( length - 1 ) )	// Get the newline character that will be taken and replace with null termination.
		{							// So in case the user enters a shorter name and hits enter then newline is string end or the maxlength is. 
			name[i] = '\0' ;		// Or even the last character taken in will also do.
			break ;
		}
	}
	char ch ;
	while ((ch = getchar()) != '\n' && ch != EOF);	/* Did not get C equivalent of cin.ignore() or cin.clear() as in C++ to flush the input stream.
							So had to google this one out. Source: http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044873249&id=1043284392 */
}

/* English characters ASCII numbers A-Z 65 to 90, a-z 97 to 122, and space is 32 */
/* Referred http://wiki.answers.com/Q/Check_whether_a_character_is_alphabaticdigital_or_special_character_using_C_program */
bool checkName( char* name )
{
	int length = strlen( name ) ;	// The given string could be shorter by the user than the default length. getData() has already put null terminator for me.
	bool namecheck = true ;	
	int i = 0 ;
	for( i = 0 ; i < length ; i++ )		// Using the postfix i++ instead of prefix saves me from missing the last one.
	{
		// If you are not a letter or a space then you are not a name. Numbers are not allowed as name.
		if( !( ( name[i] >= 'a' && name[i] <= 'z' ) || ( name[i] >= 'A' && name[i] <= 'Z' ) || ( name[i] == ' ' ) ) )
		{
			namecheck = false ;
		}
	}
	return namecheck ;
}

// Now check if the user has got away by giving all the name character as spaces.
bool allSpaces( char* name )
{
	int length = strlen( name ) ;
	int i = 0, spacecount = 0 ;
	for( i = 0 ; i < length ; i++ )		// Using the postfix i++ instead of prefix saves me from missing the last one.
	{
		if( name[i] == ' ' )
		{
			spacecount++ ;
		}
	}
	if( spacecount > ( length - 1 ) ) // Remember null termination is not included in length of the string.
	{
		return true ;
	}
	else
	{
		return false ;
	}
}

/* Check that all characters in the card number string are integers only.
 * A sort of whitelist check. Ascii character for 0 is 48 and that for 9 is 57.
 */
bool allNumerics( char* num )
{
	int length = strlen( num ) ;
	bool allnums = true ;
	int i = 0 ;
	for( i = 0 ; i < length ; i++ )		// Using the postfix i++ instead of prefix saves me from missing the last one.
	{
		if( !( num[i] >= '0' && num[i] <= '9' ) )	// If you are not a number then you should not be in this string.
		{
			allnums = false ;
		}
	}
	return allnums ;
}

void readName( char* name, int f_or_l, int length )
{
	if( f_or_l == 0 )		// Wish passing strings in C was easier. f_or_l stands for first or last as in name. 0 for first and 1 for last name.
	{
		printf( "Please enter your first name on the card.\n" ) ;
	}
	else
	{
		printf( "Please enter your last name on the card.\n" ) ;
	}
	printf( "Please note if your name may contain spaces, but cannot exceed %d characters including spaces.\n", length - 1 ) ;
    printf( "Please use only English characters, numbers or special characters cannot be accepted by the system.\n" ) ;
    getData( name, length ) ;
    while( !checkName( name ) || allSpaces( name ) )	// Keep checking till the user gets it right.
    {
    	printf( "The system seems to get only spaces, numericals or special characters.\nPlease try again.\n" ) ;
    	getData( name, length ) ;
    }
}

bool checkMonth( char* month )
{
	if( strlen( month ) != 2 )	// The length for month has been clearly demarcated at two if it is not then error.
	{
		return false ;
	}
	if( !( month[ 0 ] == '0' || month[ 0 ] == '1' ) )	// If the first digit is neither 0 nor 1 then it is a error.
	{													// You do not have months in twenties or so on.
		return false ;
	}
	if( month[ 0 ] == '1' )		// The string has already been checked for numerics. Now check that number entered was not above 12.
	{
		if( !( month[ 1 ] == '0' || month[ 1 ] == '1' || month[ 1 ] == '2' ) )	// If first number is 1 but second is not 0, 1 or 2.
		{																		// Then the month is not Oct, Nov or Dec.
			return false ;
		}
	}
	return true ;	// Default value sent back in case there was no error in input string.
}

bool checkYear( char* year )
{
	if( strlen( year ) != 4 )	// Not enough digits entered. Then the year is not valid.
	{
		return false ;
	}
	if( year[ 0 ] < '2' )	// Assured at input that every is integer. Next the year should be post 2000. 
	{						// Anything post 1999 is considered valid from 2000 to 9999.
		return false ;
	}
	return true ;	// Default true if there were no errors in input string.
}

void readNums( char* nums, int whichnum, int length )
{
	if( whichnum == 0 )		// whichnum 0 is for the 16 digit credit card number.
	{
		printf( "Please enter the 16 digit credit card number, without any spaces in between as one single 16 digit number.\n" ) ;
		printf( "Like XXXXXXXXXXXXXXXX (where each X represents a single digit).\n" ) ;
	}
	else if( whichnum == 1 )	// whichnum 1 is for 2 digit month of card expiry.
	{
		printf( "Please enter the month of expiry in digits in two digit format(XX).\n"
	    	    "For example 01 for January and 12 for December.\n" ) ;
	}
	else if( whichnum == 2 )	// whichnum 2 is for the 4 digit card expiry year.
	{
		printf( "Please enter the year of expiry in four digit format (XXXX).\n"
		   	    "For example if your card expires in year 2013, please enter complete year 2013.\n" ) ;
	}
	else if( whichnum == 3 )	// whichnum 3 for 3 digit CVV or security code.
	{
		printf( "Please enter the three digit security code at the back of the card.\n" 
		        "Please use numbers only and no spaces between the three digits like this (XXX). \n" ) ;
	}
	else if( whichnum == 4 )	// whichnum 4 for the 5 digit zipcode.
	{
		printf( "Please enter your five digit zip code in following format.(XXXXX) \n" ) ;
	}
	getData( nums, length ) ;
	while( !allNumerics( nums ) )	// Check till the user inputs all numerics.
	{
	    printf( "The system seems to be getting non numbers. Please enter numbers. \n" ) ;
	    getData( nums, length ) ;
	}
}

/* The amount is already null terminated at the maximum allowed length. 
 * So only thing to check is that it has no special characters except period, has two ending cent values.
 * Period is not repeated twice.
 */
/*bool amountCheck( char* amount, int length )
{
	if( strlen( amount ) > ( length - 1 ) )
	{
		return false ;
	}
	int i = 0, counter = 0, decimalplace = 0 ;
	for( i = 0 ; i < strlen( amount ) ; i++ )	// Check to see if there are non numericals other than period.
	{
		if( !( amount[i] >= '0' && amount[i] <= '9' ) || !( amount[ i ] == '.' ) )
		{
			return false ;
		}
		if( amount[ i ] == '.' )
		{
			if( counter == 0 )		// On the first instance of decimal point store that one.
			{						// You need that decimal place to truncate after two digits that appear after period.
				decimalplace = i ;
			}
			counter++ ;
		}
	}
	if( counter > 1 )
	{
		return false ;
	}
	if( decimalplace > ( length - 3 ) )		// There are not enough digits after decimal point.
	{
		return false ;
	}
	amount[ decimalplace + 3 ] = '\0' ;	// Truncate after period. So if anybody enters .090809432. The return is .09 only.
	return true ;
}*/

void readAmount( char* amount, int length )
{
	printf( "Please enter the the purchase amount.\n"
	        "Please input only digits without any spaces in between and do include the cents value as continously in digits.\n"
		    "For example $10.01 should be entered as 1001.\n") ;
	getData( amount, length ) ;
	while( !allNumerics( amount ) )
	{
		printf( "Seems to have non numerical characers in. Please try again.\n" ) ;
		getData( amount, length ) ;
	}
}

/* The email function will only accept alphanumerics and @, period and underscore in email name.
 * More than one @ symbol will be flagged. After the @ there needs to be atleast one period sign.
 * There needs to be atleast two characters before @ with one letter and number. So minimal requirement X1@X1.XX for email.
 * At max the email can be a.b.c__dae@jka.234.sfgsd.jkllk
 */
bool emailCheck( char* email, int length )
{
	/*if( strlen( email ) > ( length - 1 ) )
	{
		return false ;
	}*/
	int i = 0, counter = 0, domainpos = 0 ;
	for( i = 0 ; i < strlen( email ) ; i++ )  // Check to see it does not have any non allowed characters.
	{
		if( !( ( email[i] >= 'a' && email[i] <= 'z' ) || ( email[i] >= 'A' && email[i] <= 'Z' ) 
			|| ( email[i] >= '0' && email[i] <= '9' ) || ( email[i] == '@' ) || ( email[i] == '_') || ( email[i] == '.' ) ) )
		{
			return false ;
		}
		if( email[i] == '@' )
		{
			if( counter == 0 )
			{
				domainpos = i ;
			}
			counter++ ;
		}
	}
	/*if( ( domainpos < 2 ) || ( domainpos > strlen( email ) - 4 ) ) // Make sure the @ sign is not the first one or comes after one character.
	{                                                              // The ending format @X.XX has to be achieved so length - 4 for that.
		return false ;
	}
	if( counter > 1 )	// If more than one @ symbol then flag as error.
	{
		return false ;
	}
	if( ( email[ domainpos -1 ] == '.' ) || ( email[ domainpos + 1 ] == '.' ) ) // If there is period just after or before @ sign
	{																			// then reject the same.
		return false ;
	}
	for( i = strlen( email ) ; i > 0 ; i-- )
	{
		if( email[i] == '.' )
		{
			domainpos = i ;
			break ;
		}
	}
	if( ( domainpos == strlen( email ) ) || ( domainpos == ( strlen( email ) - 1 ) ) )  // If last position. or position just before that is 
	{															// period then wrong formatting. Flag and return false.
		return false ;
	}
	for( i = strlen( email ) ; i > domainpos ; i-- )  // Lastly there are alphabets only after the last period.
	{												  // So it ends like @jkj.XX not @sda.12 all domain names end with two letters.
		if( !( ( email[i] >= 'a' && email[i] <= 'z' ) || ( email[i] >= 'A' && email[i] <= 'Z' ) ) )
		{
			return false ;
		}
	}*/
	return true ;	// Default if no errors in the input stream then return true.
}

// Function to read the email.
void readEmail( char* email, int length )
{
	printf( "Please enter your email address.\n" 
			"Please note that if your email address is more than 30 characters then it may be rejected or truncated.\n" ) ;
	getData( email, length ) ;
	while( !emailCheck( email, length ) )
	{
		printf( "Invalid email format. Please try again. \n" ) ;
		getData( email, length ) ;
	}
}

/* The display function. */
void display( char* fname, char* lname, char* cardnum, char* month, char* year, char* cvv, char* zip,
              char* amount, char* email )
{
	printf( "Name\t \t \t \t  %s %s \n", fname, lname ) ;
	printf( "Credit card number \t \t%s \n", cardnum ) ;
	printf( "Expiration month and year\t " ) ;
	if( ( ( month[0] == '0' ) && ( month[ 1 ] == '0' ) ) || ( ( month[0] == '0' ) && ( month[ 1 ] == '1' ) ) )
	{ printf( "January " ) ; }
	if( ( month[0] == '0' ) && ( month[ 1 ] == '2' ) )
	{ printf( "February " ) ; }
	if( ( month[0] == '0' ) && ( month[ 1 ] == '3' ) )
	{ printf( "March " ) ; }
	if( ( month[0] == '0' ) && ( month[ 1 ] == '4' ) )
	{ printf( "April " ) ; }
	if( ( month[0] == '0' ) && ( month[ 1 ] == '5' ) )
	{ printf( "May " ) ; }
	if( ( month[0] == '0' ) && ( month[ 1 ] == '6' ) )
	{ printf( "June " ) ; }
	if( ( month[0] == '0' ) && ( month[ 1 ] == '7' ) )
	{ printf( "July " ) ; }
	if( ( month[0] == '0' ) && ( month[ 1 ] == '8' ) )
	{ printf( "August " ) ; }
	if( ( month[0] == '0' ) && ( month[ 1 ] == '9' ) )
	{ printf( "September " ) ; }
	if( ( month[0] == '1' ) && ( month[ 1 ] == '0' ) )
	{ printf( "October " ) ; }
	if( ( month[0] == '1' ) && ( month[ 1 ] == '1' ) )
	{ printf( "November " ) ; }
	if( ( month[0] == '1' ) && ( month[ 1 ] == '2' ) )
	{ printf( "December " ) ; }
	printf( "%s\n", year ) ;
	printf( "Security Code \t \t \t %s\n", cvv ) ;
	printf( "Zip Code\t \t \t  %s\n", zip ) ;
	printf( "Purchase amount \t \t" ) ;
	int i = 0 ;
	for( i = 0 ; i < ( strlen(amount) - 2 ) ; i++ )
	{
		printf( "%c", amount[ i ] ) ;
	}
	printf( "." ) ;
	for( i = ( strlen(amount) - 2 ) ; i < strlen(amount) ; i++ )
	{
		printf( "%c", amount[ i ] ) ;
	}
	printf( "\n" ) ;
	printf( "Email address \t \t \t %s\n", email ) ;
}

/* The actual read function. */
void readin()
{
	char* fname = ( char* )malloc( sizeof( char ) * 26 ) ;	// The extra length for the null terminator.
    readName( fname, 0, 26 ) ;
    char* lname = ( char* )malloc( sizeof( char ) * 31 ) ;
	readName( lname, 1, 31 ) ;
	char* cardnum = ( char* )malloc( sizeof( char ) * 17 ) ;
	readNums( cardnum, 0, 17 ) ;
	char* month = ( char* )malloc( sizeof( char ) * 3 ) ;
	readNums( month, 1, 3 ) ;
	while( !checkMonth( month ) )
	{
		printf( "The entered month is not valid. Please try again.\n" ) ;
		readNums( month, 1, 3 ) ;
	}
	char* year = ( char* )malloc( sizeof( char ) * 5 ) ;
	readNums( year, 2, 5 ) ;
	while( !checkYear( year ) )
	{
		printf( "The entered year is not valid. Please try again.\n" ) ;
		readNums( year, 2, 5 ) ;
	}
	char* cvv = ( char* )malloc( sizeof( char ) * 4 ) ;
	readNums( cvv, 3, 4 ) ;
	if( strlen( cvv ) != 3 )	// String already checked for numbers. Check if all three are there.
	{
		printf( "Not enough digits for 3 digit CVV security code. Please try again. \n" ) ;
		readNums( cvv, 3, 4 ) ;
	}
	char* zip = ( char* )malloc( sizeof( char ) * 6 ) ;
	readNums( zip, 4, 6 ) ;
	if( strlen( zip ) != 5 )
	{
		printf( "Not enough numbers for 5 digit zipcode. Please try again.\n" ) ;
		readNums( zip, 4, 6 ) ;
	}
	char* amount = ( char* )malloc( sizeof( char ) * 10 ) ;
	readAmount( amount, 10 ) ;
	char* email = ( char* )malloc( sizeof( char ) * 25 ) ;
	readEmail( email, 31 ) ;
	display( fname, lname, cardnum, month, year, cvv, zip, amount, email ) ;
	// Free up all the memory pointers used here.
	free( fname ) ;	free( lname ) ;	free( cardnum ) ; free( month ) ; free( year ) ;
	free( cvv ) ; free( zip ) ; free( amount ) ; free( email ) ;
}

int main()
{
	readin() ;
	return 0 ;
}

/* 
The program is kind of wonky when taking in input since of the new line trash.
Also if you enter more than extra arguments in month, year, CVV it truncates.
Sample Run:
soham@Kathryn:/host/Users/Soham/workspace/secure coding$ gcc -c sanitize_string.c
soham@Kathryn:/host/Users/Soham/workspace/secure coding$ gcc -o sanitize sanitize_string.o
soham@Kathryn:/host/Users/Soham/workspace/secure coding$ ./sanitize
Please enter your first name on the card.
Please note if your name may contain spaces, but cannot exceed 25 characters including spaces.
Please use only English characters, numbers or special characters cannot be accepted by the system.
adfdsa asdfasd adsfasdf

Please enter your last name on the card.
Please note if your name may contain spaces, but cannot exceed 30 characters including spaces.
Please use only English characters, numbers or special characters cannot be accepted by the system.
afdsasdf adsf asd fa 

Please enter the 16 digit credit card number, without any spaces in between as one single 16 digit number.
Like XXXXXXXXXXXXXXXX (where each X represents a single digit).
243235325234524352435423543
Please enter the month of expiry in digits in two digit format(XX).
For example 01 for January and 12 for December.
1234
Please enter the year of expiry in four digit format (XXXX).
For example if your card expires in year 2013, please enter complete year 2013.
354523534552
Please enter the three digit security code at the back of the card.
Please use numbers only and no spaces between the three digits like this (XXX). 
4536346436
Please enter your five digit zip code in following format.(XXXXX) 
645364564346
Please enter the the purchase amount.
Please input only digits without any spaces in between and do include the cents value as continously in digits.
For example $10.01 should be entered as 1001.
25453646546546354765765
Please enter your email address.
Please note that if your email address is more than 30 characters then it may be rejected or truncated.
534353@53345.55436

Name	 	 	 	  adfdsa asdfasd adsfasdf afdsasdf adsf asd fa  
Credit card number 	 	2432353252345243 
Expiration month and year	 December 3545
Security Code 	 	 	 453
Zip Code	 	 	  64536
Purchase amount 	 	2545364.65
Email address 	 	 	 534353@53345.55436
*/
