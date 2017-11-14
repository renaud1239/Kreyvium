
#include <iostream>
using namespace std;
#include <assert.h>

#define __VERBOSE__

template<typename bit>
void readKeyAndRunKreyvium(void)
{

	bit key[128],iv[128],s[288];

	bit RKEY[128],RIV[128]; // The two additional LFSR.
	
	for(int i=0;i<128;i++)
		cin>>key[i];
	for(int i=0;i<128;i++)
		cin>>iv[i];

#ifdef __VERBOSE__
	cout<<"key = ";
	for(int i=0;i<128;i++)
		cout<<key[i]<<" ";
	cout<<endl;
#endif
	
#ifdef __VERBOSE__
	cout<<"iv = ";
	for(int i=0;i<128;i++)
		cout<<iv[i]<<" ";
	cout<<endl;
#endif
		
	// Internal state setup.
	for(int i=0;i<288;i++)
		s[i]=bit(1);
	// Insert the first 93 key bits @ position 0 (1 in the paper).
	for(int i=0;i<93;i++)
		s[i]=key[i];
	// Insert the first 84 iv bits @ position 93 (94 in the paper).
	for(int i=0;i<84;i++)
		s[i+93]=iv[i];
	// Insert the remaining iv bits @ position 177 (178 in the paper).
	for(int i=0;i<44;i++)
		s[i+177]=iv[i+84];
	// Set pos 287 to 0 (288 in the paper).	
	s[287]=bit(0);
	
	// RKEY register set up.
	for(int i=0;i<128;i++)
		RKEY[i]=key[128-i-1];
	// RIV register setup.
	for(int i=0;i<128;i++)
		RIV[i]=iv[128-i-1];
		
#ifdef __VERBOSE__
	cout<<"s = ";
	for(int i=0;i<288;i++)
		cout<<s[i]<<" ";
	cout<<endl;
#endif

	// Internal state warm up.
	for(int i=0;i<4*288;i++)
	{
		bit t1=s[65]^s[90]&s[91]^s[92]^s[170]^RIV[127-0]; // t1 = s66+s91*s92+s93+s171+RIV[0] (paper).
		bit t2=s[161]^s[174]&s[175]^s[176]^s[263]; // t2 = s162+s175*s176+s177+s264 (paper).
		bit t3=s[242]^s[285]&s[286]^s[287]^s[68]^RKEY[127-0]; // t3 = s243+s286*s287+s288+s69+RKEY[0] (paper).
		bit t4=RKEY[127-0];
		bit t5=RIV[127-0];
		// Shift the internal state from 1 to the right.
		for(int j=0;j<287;j++)
			s[288-j-1]=s[288-j-2];
		// Then inject the ti's.
		s[0]=t3; // s1 = t3 (paper).
		s[93]=t1; // s94 = t1 (paper).
		s[177]=t2; // s178 = t2 (paper).
		// Shift RKEY and RIV from 1 to the right.
		for(int j=0;j<127;j++)
		{
			RKEY[128-j-1]=RKEY[128-j-2];
			RIV[128-j-1]=RIV[128-j-2];
		}
		// Then injects t4 and t5.
		RKEY[0]=t4;
		RIV[0]=t5;
	}

#ifdef __VERBOSE__
	cout<<"s = ";
	for(int i=0;i<288;i++)
		cout<<s[i]<<" ";
	cout<<endl;
#endif
	
	// Keystream generation.
	for(int i=0;i<46;i++)
	{
		bit t1=s[65]^s[92]; // t1 = s66+s93 (paper).
		bit t2=s[161]^s[176]; // t2 = s162+s177 (paper).
		bit t3=s[242]^s[287]^RKEY[127-0]; // t3 = s243+s288+RKEY[0] (paper).
		bit z=t1^t2^t3; // zi = t1+t2+t3 (paper).
		t1=t1^s[90]&s[91]^s[170]^RIV[127-0]; // t1 = t1+s91*s92+s171 (paper).
		t2=t2^s[174]&s[175]^s[263]; // t2 = t2+s175*s176+s264 (paper).
		t3=t3^s[285]&s[286]^s[68]; // t3 = t3+s286*s287+s69 (paper).
		bit t4=RKEY[127-0];
		bit t5=RIV[127-0];
		// Shift the internal state from 1 to the right.
		for(int j=0;j<287;j++)
			s[288-j-1]=s[288-j-2];
		// Then inject the ti's.
		s[0]=t3; // s1 = t3 (paper).
		s[93]=t1; // s94 = t1 (paper).
		s[177]=t2; // s178 = t2 (paper).	
		// Shift RKEY and RIV from 1 to the right.
		for(int j=0;j<127;j++)
		{
			RKEY[128-j-1]=RKEY[128-j-2];
			RIV[128-j-1]=RIV[128-j-2];
		}
		// Then injects t4 and t5.
		RKEY[0]=t4;
		RIV[0]=t5;
		
        cout<<z<<" ";
	}
	
}

int main(void)
{
	readKeyAndRunKreyvium<int>();

	return 0;
}
