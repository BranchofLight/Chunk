// TO DO based on priority
// int find(Chunk&) - reference string->find

#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class Chunk
{
	public:
		Chunk();
		Chunk(const Chunk&);
		Chunk(const char[]);
		Chunk(const char);
		Chunk(const std::string);
		Chunk(const int);
		Chunk(const float);
		~Chunk();

		Chunk subchunk(int, int) const;
		int   find(Chunk&) const;

		void  clear() { chunk.clear(); }
		int   length() const { return chunk.size(); }
		bool  isEmpty() const { return length() == 0; }

		bool  greaterThan(const Chunk&) const;
		bool  lesserThan(const Chunk&) const;

		bool isInteger() const;
		bool isFloat() const;
		
		std::string toString() const;
		int         toInt() const;		
		float       toFloat() const;

		// --------------------------------------
		// --------------------------------------
		// --------- Operator Overloads ---------
		// --------------------------------------
		// --------------------------------------

		char& operator[](int index);
		char operator[](int index) const;
		Chunk& operator=(Chunk rhs); 

		bool operator==(const Chunk&) const;
		bool operator!=(const Chunk&) const;

		inline bool operator< (const Chunk& rhs) const;
		inline bool operator> (const Chunk& rhs) const;

		inline bool operator<=(const Chunk& rhs)  const {return !(*this > rhs);}
		inline bool operator>=(const Chunk& rhs)  const {return !(*this < rhs);}

		friend std::ostream& operator<<(std::ostream& os, const Chunk& obj)
		{
			// Write each character to the stream
			for (int i = 0; i < obj.length(); i++)
				os << obj[i];

			return os;
		}
		
		friend std::istream& operator>>(std::istream& is, Chunk& obj)
		{			
			// Create container the stream can write to
			char *input = new char[MAX_SIZE_STREAM];
			// Write to it
			is >> input;
			// Use the copy constructor to give obj the data from input
			obj = input;
			// Free memory and return
			delete[] input;
			return is;
		}

		friend void getchunk(std::istream& is, Chunk& obj)
		{
			// Create container the stream can write to
			char *input = new char[MAX_SIZE_STREAM];

			// Gets the entire line
			is.getline(input, MAX_SIZE_STREAM);

			// Sets object
			obj = input;

			// Free memory
			delete[] input;
		}
		
		Chunk& operator+=(const Chunk& rhs);
		friend inline Chunk operator+(Chunk lhs, const Chunk& rhs)
		{
			// lhs is a copy so simply using += is safe
			lhs += rhs;
			return lhs;
		}

		// ------------------------------------
		// ------------------------------------
		// ------- End of Public Scope --------
		// ------------------------------------
		// ------------------------------------

	private:
		void add(char c) { return chunk.push_back(c); }		

		std::vector<char> chunk;

		static const int MAX_SIZE_STREAM;
};



