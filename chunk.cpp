#include "chunk.h"

// The max size a chunk will be when created from a stream
// Non-stream created chunks' max size are based on vector's
const int Chunk::MAX_SIZE_STREAM = 255;

Chunk::Chunk()
{ 
	chunk = std::vector<char>();
}

// Copy Constructor
Chunk::Chunk(const Chunk& newChunk)
{
	// Pushes all the characters from newChunk on this
	for (int i = 0; i < newChunk.length(); i++)
		this->chunk.push_back(newChunk[i]);
}

// Conversion Constructor for literals and char arrays
Chunk::Chunk(const char newChars[])
{
	// Pushes all the characters from newChars on this
	// Note: stops at null terminator character
	for (int i = 0; newChars[i] != '\0'; i++)
		this->chunk.push_back(newChars[i]);
}

// Conversion Constructor for chars
Chunk::Chunk(const char newChar)
{
	this->chunk.push_back(newChar);
}

// Conversion Constructor for strings
Chunk::Chunk(std::string rhs)
{
	for (unsigned int i = 0; i < rhs.length(); i++)
		chunk.push_back(rhs[i]);
}

// Conversion Constructor for ints
Chunk::Chunk(int rhs)
{
	std::stringstream ss;
	ss << rhs;

	*this = ss.str();
}

// Conversion Constructor for floats
Chunk::Chunk(float rhs)
{
	std::stringstream ss;
	ss << rhs;

	*this = ss.str();
}

// Destructor 
Chunk::~Chunk()
{
}

// Returns a Chunk with all characters from start to but not including end
Chunk Chunk::subchunk(int start, int end) const
{
	Chunk newChunk;

	// Adds the appropriate chars to the newChunk
	// If the end is greater than start it will return an empty Chunk
	for (int i = start; i < end; i++)
	{
		newChunk.add((*this)[i]); // Using the Chunk[] instead of vector[] allows it to handle outofbounds exceptions
	}

	return newChunk;
}

// Does a greater than check for alphabetical order
bool Chunk::greaterThan(const Chunk& rhs) const
{
	Chunk c = rhs;
	return rhs > *this;
}

// Does a lesser than check for alphabetical order
bool Chunk::lesserThan(const Chunk& rhs) const
{
	Chunk c = rhs;
	return rhs.greaterThan(*this);
}

// Returns a std::string of the Chunk
std::string Chunk::toString() const
{
	std::string str = "";

	for (int i = 0; i < length(); i++)
		str += (*this)[i];

	return str;
}

// Returns an int of the Chunk
int Chunk::toInt() const
{
	if (isInteger() && length() > 0)
	{
		std::stringstream ss;
		ss << toString();

		int newInt;
		ss >> newInt;

		return newInt;
	}
	else if (length() == 0)
		throw std::bad_cast("Cannot be cast. Chunk is empty.");
	else 
		throw std::bad_cast("Cannot be cast. Chunk has non-integer value(s).");
}

// Returns a float of the Chunk
float Chunk::toFloat() const
{
	if (isFloat() && length() > 0)
	{
		std::stringstream ss;
		ss << toString();

		float newFloat;
		ss >> newFloat;

		return newFloat;
	}
	else if (length() == 0)
		throw std::bad_cast("Cannot be cast. Chunk is empty.");		
	else 
		throw std::bad_cast("Cannot be cast. Chunk has a non-float value.");
}

// Gets address of a character at index 
// This version is not promised to be constant
char& Chunk::operator[](int index)
{
	int len = length();
	if (index < 0 || index >= length())
	{
		std::stringstream ss;
		ss << "Index out of range: (Index: " << index << ", Length: " << length() << ")"; 
		throw std::out_of_range(ss.str());
	}

	return char(chunk[index]);
}

// Gets address of a character at index 
// This version is promised to be constant
char Chunk::operator[](int index) const
{
	int len = length();
	if (index < 0 || index >= length())
	{
		std::stringstream ss;
		ss << "Index out of range: (Index: " << index << ", Length: " << length() << ")"; 
		throw std::out_of_range(ss.str());
	}

	return char(chunk[index]);
}

// Assignment operator
Chunk& Chunk::operator=(Chunk rhs)
{
	// Clears the vector before pushing rhs on this
	chunk.clear();

	for (int i = 0; i < rhs.length(); i++)
		chunk.push_back(rhs[i]);

	return *this;
}

// Equality operator
bool Chunk::operator==(const Chunk& rhs) const
{
	// The lengths are not the same
	if (length() != rhs.length())
		return false;
	else
	{
		// Any character is not the same
		for (int i = 0; i < length(); i++)
		{
			if (chunk[i] != rhs[i])
				return false;
		}
	}

	// At this point they're the same
	return true;
}

// Inequality operator
bool Chunk::operator!=(const Chunk& rhs) const
{
	return !(*this==rhs);
}

// 
Chunk& Chunk::operator+=(const Chunk& rhs)
{
	// Add the characters of the rhs to the lhs (this)
	for (int i = 0; i < rhs.length(); i++)
	{
		this->add(rhs[i]);
	}
		
	return *this;
}

// Relational operator
bool Chunk::operator< (const Chunk& rhs) const
{
	// Get the shortest length Chunk
	int len;
	if (length() < rhs.length())
		len = length();
	else
		len = rhs.length();

	for (int i = 0; i < len; i++)
	{
		// If characters are the same
		// the loop will continue
		if (chunk[i] > rhs[i])
		{
			return false;
		}
		else if (chunk[i] < rhs[i])
		{
			return true;
		}
	}

	// If all of the characters checked are the same
	if (length() == rhs.length())
	{
		return false;
	}
	else if (length() > rhs.length())
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Relational operator
bool Chunk::operator> (const Chunk& rhs) const
{ 
	// Swaps rhs with lhs in check
	// Need to reinitialize rhs due to non-const requirement
	Chunk c = rhs;
	return c < *this;
}

// Determines if the Chunk is made up of only integers
bool Chunk::isInteger() const
{
	for (int i = 0; i < length(); i++)
	{
		if (chunk[i] == '-' && i == 0)
			continue;

		if (chunk[i] < '0' || chunk[i] > '9')
			return false;
	}

	return true;
}

// Determines if the Chunk is a float
bool Chunk::isFloat() const
{
	// If it is an integer it can be a float
	if (isInteger())
		return true;

	// Used to make sure a decimal is present
	bool decimalFound = false;

	for (int i = 0; i < length(); i++)
	{
		// Make sure a decimal exists
		if (chunk[i] == '.')
		{
			// Makes sure this decimal is the only decimal in the Chunk
			if (decimalFound)
				return false;

			// Makes sure the decimal is not the first or last character
			if (i == 0 || i == length()-1)
				return false;

			decimalFound = true;
			continue;
		}

		if (chunk[i] < '0' || chunk[i] > '9')
			return false;
	}

	// Returns true if the decimal was found
	return decimalFound;
}