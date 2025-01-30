#include "Zipper.h"
#define ZLIB_WINAPI
#include "zlib.h"
#include <fstream>
#include <vector>
#include "Debug_Log.h"
#include "../Core.h"

// Constructor taking a pointer to the game engine's Core object
ArksEngine::Zipper::Zipper(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
{
}

// Method to load and unzip the contents of a zip file
bool ArksEngine::Zipper::LoadZipFile(const char* fileName)
{
	// Open the assets zip
	std::ifstream assetsFile(fileName, std::ios::in | std::ios::binary);

	// Check if the file is opened successfully
	if (!assetsFile.is_open())
	{
		// Log error and return false if the file failed to open
		m_pOwner->GetDebug_Log()->Error("Failed to open Assets");
		return false;
	}

	// Log message for successful file opening
	m_pOwner->GetDebug_Log()->Log("Opened Assets file");

	// Read Header

	// Calculate the offset for the zip header
	std::streamoff zipHeaderOffset = -static_cast< std::streamoff>(sizeof(mZipHeader));

	// Set the position to the beginning of the zip header
	assetsFile.seekg(zipHeaderOffset, std::ios::end);

	// Read the zip header
	assetsFile.read(reinterpret_cast<char*>(&mZipHeader), sizeof(mZipHeader));

	// Check if the file is a valid zip file
	if (mZipHeader.signature != kZipSignature)
	{
		// Log error and return false if the file is not a valid zip file
		m_pOwner->GetDebug_Log()->Error("This file is not a zip file");
		return false;
	}

	// Log message for successful zip file identification
	m_pOwner->GetDebug_Log()->Log("This is a Zip file");

	// Read the dir data
	// Its a array of file headers

	// Calculate the offset for the directory data
	std::streamoff dirOffset = mZipHeader.dirOffset;
	assetsFile.seekg(dirOffset, std::ios::beg);

	// Allocate memory for the directory data and read it from the file
	std::vector<char> dirData(mZipHeader.dirSize, 0);
	assetsFile.read(dirData.data(), mZipHeader.dirSize);

	// Cast the pointer to the directory data to a FileHeader pointer
	auto pFileHeader = reinterpret_cast<FileHeader*>(dirData.data());


	// looping through all file headers
	for (int iFile = 0; iFile < mZipHeader.numFiles; ++iFile)
	{
		// Check if the file header has the correct signature
		if (pFileHeader->signature != kFileSignature)
		{
			// Log error and return false if the file header signature is incorrect
			m_pOwner->GetDebug_Log()->Error("File signature failed");
			return false;
		}

		// Get the file name from the file header
		char* pNamePtr = reinterpret_cast<char*>(pFileHeader + 1);
		std::string file_name(pNamePtr, pFileHeader->nameLength);

		// Log the file name
		m_pOwner->GetDebug_Log()->Log(file_name);

		// Get the data header and unzip the file
		DataHeader dataHeader;
		assetsFile.seekg(pFileHeader->dataOffset, std::ios::beg);
		assetsFile.read(reinterpret_cast<char*>(&dataHeader), sizeof(dataHeader));

		// Check if the data header has the correct signature
		if (dataHeader.signature != kDataSignature)
		{
			// Log error and return false if the data header signature is incorrect
			m_pOwner->GetDebug_Log()->Error("Data signature failed");
			return false;
		}

		// Move the file pointer to the beginning of the file data
		assetsFile.seekg(dataHeader.nameLength, std::ios::cur);

		// Read the compressed data from the file
		std::vector<char> data(dataHeader.compressedSize);
		assetsFile.read(data.data(), dataHeader.compressedSize);

		// Allocate memory for the uncompressed data
		std::vector<char> buffer(dataHeader.uncompressedSize);

		// Uncompress the file data if it is compressed using DEFLATE algorithm
		if (dataHeader.compression == Z_DEFLATED)
		{
			// (Uncompression code using zlib)
			z_stream zStream;
			zStream.next_in = (Bytef*)data.data();
			zStream.avail_in = (uInt)dataHeader.compressedSize;

			zStream.next_out = (Byte*)buffer.data();
			zStream.avail_out = (uInt)dataHeader.uncompressedSize;

			zStream.zalloc = (alloc_func)0;
			zStream.zfree = (free_func)0;

			// UNCOMPRESS	
			int zStatus = inflateInit2(&zStream, -MAX_WBITS);

			if (zStatus == Z_OK)
			{
				zStatus = inflate(&zStream, Z_FINISH);
				inflateEnd(&zStream);

				if (zStatus == Z_STREAM_END)
				{
					zStatus = Z_OK;
				}

				// You have to end the inflation again!!!!!
				inflateEnd(&zStream);
			}

  		}

		// Store the unzipped data in the unordered_map
		m_unzippedAssets[file_name] = std::move(buffer);

		// Move the pointer to the next file header
		pFileHeader = reinterpret_cast<FileHeader*>(pNamePtr + pFileHeader->nameLength);
	}

	// Log the success
	m_pOwner->GetDebug_Log()->Log("All Data signature succeeded");

	return true;
}
