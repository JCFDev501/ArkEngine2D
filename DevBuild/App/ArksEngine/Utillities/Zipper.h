#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

static constexpr uint32_t kZipSignature = 0x06054b50;

#pragma pack(1)
struct ZipHeader
{
	uint32_t signature = 0;
	uint16_t diskIndex = 0;
	uint16_t startDisk = 0;
	uint16_t numFiles = 0;
	uint16_t totalFiles = 0;
	uint32_t dirSize = 0;
	uint32_t dirOffset = 0;
	uint16_t commentLength = 0;
};
#pragma pack()

static constexpr uint32_t kFileSignature = 0x02014b50;

#pragma pack(1)
struct FileHeader
{
	uint32_t signature = 0;
	uint16_t versionMade = 0;
	uint16_t versionNeeded = 0;
	uint16_t flag = 0;
	uint16_t compression = 0;
	uint16_t time = 0;
	uint16_t date = 0;
	uint32_t crcCode = 0;
	uint32_t compressedSize = 0;
	uint32_t uncompressedSize = 0;
	uint16_t nameLength = 0;
	uint16_t extraLength = 0;
	uint16_t commentLength = 0;
	uint16_t startDisk;
	uint16_t internalAttributes;
	uint32_t externalAttributes;
	uint32_t dataOffset;
};
#pragma pack()

static constexpr uint32_t kDataSignature = 0x04034b50;

#pragma pack(1)
struct DataHeader
{
	uint32_t signature = 0;
	uint16_t version = 0;
	uint16_t flag = 0;
	uint16_t compression = 0;
	uint16_t time = 0;
	uint16_t date = 0;
	uint32_t crcCode = 0;
	uint32_t compressedSize = 0;
	uint32_t uncompressedSize = 0;
	uint16_t nameLength = 0;
	uint16_t extraLength = 0;
};
#pragma pack()

namespace ArksEngine
{
	class Core;

	class Zipper
	{
		ArksEngine::Core* m_pOwner;
		ZipHeader mZipHeader;
		std::unordered_map<std::string, std::vector<char>> m_unzippedAssets;

	public:
		Zipper(ArksEngine::Core* pOwner);
		~Zipper() = default;

		bool LoadZipFile(const char* fileName);

		std::unordered_map<std::string, std::vector<char>> Get_UnzippedAssets() { return m_unzippedAssets; }
	};
}


