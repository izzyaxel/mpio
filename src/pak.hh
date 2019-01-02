#pragma once

#include "util.hh"
#include "datatypes/fourCC.hh"

struct ResourceTable
{
	i32 compressionFlag;
	FourCC assetType;
	i32 assetID, size, offset;
};

struct NamedResource
{
	FourCC assetType;
	i32 assetID, nameLength;
	std::string nameString;
};

struct PAK
{
	i16 majorVersion = 3, minorVersion = 5, unused1 = 0;
	i32 namedResourceCount = 0, resourceCount = 0;
	Vector<ResourceTable> resourceTable;
	Vector<NamedResource> namedResourceTable;
};
