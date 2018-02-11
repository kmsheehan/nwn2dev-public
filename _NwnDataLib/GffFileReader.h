/*++

Copyright (c) Ken Johnson (Skywing). All rights reserved.

Module Name:

	GffFileReader.h

Abstract:

	This module defines the interface to the Generic File Format (GFF) file
	reader.  GFF files contain extensible structures of many data types,
	particularly those emitted by the area creation toolset.

--*/

#ifndef _PROGRAMS_NWN2DATALIB_GFFFILEREADER_H
#define _PROGRAMS_NWN2DATALIB_GFFFILEREADER_H

#ifdef _MSC_VER
#pragma once
#endif

#include "FileWrapper.h"
#include "Precomp.h"
//#include "../_NwnUtilLib/Ref.h"
//#include "../_NwnBaseLib/ModelSystem.h"
//#include "../_NwnBaseLib/BaseConstants.h"

class ResourceManager;

//
// Define the GFF file reader object, used to access GFF files.
//

class GffFileReader
{

public:

	typedef swutil::SharedPtr< GffFileReader > Ptr;

	class GffStruct;

	typedef enum _GFF_LANGUAGE
	{
		LangEnglish            = 0,
		LangFrench             = 1,
		LangGerman             = 2,
		LangItalian            = 3,
		LangSpanish            = 4,
		LangPolish             = 5,
		LangKorean             = 128,
		LangChineseTraditional = 129,
		LangChineseSimplified  = 130,
		LangJapanese           = 131,
		LangLastGFFLanguage
	} GFF_LANGUAGE, * PGFF_LANGUAGE;

	//
	// Constructor.  Raises an std::exception on parse failure.
	//

	GffFileReader(
		 const std::string & FileName,
		 ResourceManager & ResMan
		);

	GffFileReader(
		 const void * GffRawData,
		 size_t DataSize,
		 ResourceManager & ResMan
		);

	//
	// Destructor.
	//

	virtual
	~GffFileReader(
		);

	//
	// Set the default localization language.
	//

	inline
	void
	SetDefaultLanguage(
		 GFF_LANGUAGE Language
		)
	{
		m_Language = Language;
	}

	inline
	GFF_LANGUAGE
	GetDefaultLanguage(
		) const
	{
		return m_Language;
	}

	//
	// Return the GFF type (from the header).
	//

	inline
	unsigned long
	GetFileType(
		) const
	{
		return m_Header.FileType;
	}

	//
	// Get the root structure for the file.
	//

	inline
	const GffStruct *
	GetRootStruct(
		) const
	{
		return &m_RootStruct;
	}

private:

	//
	// Parse the on-disk format and read the base directory data in.
	//

	void
	ParseGffFile(
		);

public:

	//
	// Define the GFF on-disk file structures.  This data is based on the
	// BioWare Aurora engine documentation.
	//
	// http://nwn.bioware.com/developers/Bioware_Aurora_GFF_Format.pdf
	//

//#include <pshpack1.h>

	typedef enum _GFF_FIELD_TYPE
	{
		GFF_BYTE          = 0,
		GFF_CHAR          = 1,
		GFF_WORD          = 2,
		GFF_SHORT         = 3,
		GFF_DWORD         = 4,
		GFF_INT           = 5,
		GFF_DWORD64       = 6,
		GFF_INT64         = 7,
		GFF_FLOAT         = 8,
		GFF_DOUBLE        = 9,
		GFF_CEXOSTRING    = 10,
		GFF_RESREF        = 11,
		GFF_CEXOLOCSTRING = 12,
		GFF_VOID          = 13,
		GFF_STRUCT        = 14,
		GFF_LIST          = 15,
		GFF_RESERVED      = 16,
		GFF_VECTOR        = 17,

		LAST_GFF_FIELD_TYPE

	} GFF_FIELD_TYPE, * PGFF_FIELD_TYPE;

	typedef unsigned long GFF_COUNT;
	typedef unsigned long STRUCT_INDEX;
	typedef unsigned long FIELD_INDEX;
	typedef unsigned long LABEL_INDEX;
	typedef unsigned long FIELD_DATA_INDEX;
	typedef unsigned long FIELD_INDICIES_INDEX;
	typedef unsigned long LIST_INDICIES_INDEX;

	typedef struct _GFF_HEADER
	{
		unsigned long FileType;                // "GFF "
		unsigned long Version;                 // "V3.2"
		unsigned long StructOffset;            // Offset of Struct array as bytes from the beginning of the file
		unsigned long StructCount;             // Number of elements in Struct array
		unsigned long FieldOffset;             // Offset of Field array as bytes from the beginning of the file
		unsigned long FieldCount;              // Number of elements in Field array
		unsigned long LabelOffset;             // Offset of Label array as bytes from the beginning of the file
		unsigned long LabelCount;              // Number of elements in Label array
		unsigned long FieldDataOffset;         // Offset of Field Data as bytes from the beginning of the file
		unsigned long FieldDataCount;          // Number of bytes in Field Data block
		unsigned long FieldIndiciesOffset;     // Offset of Field Indicies array as bytes from the beginning of the file
		unsigned long FieldIndiciesCount;      // Number of bytes in Field Indicies array
		unsigned long ListIndiciesOffset;      // Offset of List Indicies array as bytes from the beginning of the file
		unsigned long ListIndiciesCount;       // Number of bytes in List Indicies array
	} GFF_HEADER, * PGFF_HEADER;

	typedef const struct _GFF_HEADER * PCGFF_HEADER;
	
	typedef struct _GFF_STRUCT_ENTRY
	{
		unsigned long Type;
		unsigned long DataOrDataOffset;
		unsigned long FieldCount;
	} GFF_STRUCT_ENTRY, * PGFF_STRUCT_ENTRY;

	typedef const struct _GFF_STRUCT_ENTRY * PCGFF_STRUCT_ENTRY;
	
	typedef struct _GFF_FIELD_ENTRY
	{
		unsigned long Type;
		unsigned long LabelIndex;
		unsigned long DataOrDataOffset;
	} GFF_FIELD_ENTRY, * PGFF_FIELD_ENTRY;

	typedef const struct _GFF_FIELD_ENTRY * PCGFF_FIELD_ENTRY;
	
	typedef struct _GFF_LABEL_ENTRY
	{
		char Name[ 16 ];
	} GFF_LABEL_ENTRY, * PGFF_LABEL_ENTRY;

	typedef const struct _GFF_LABEL_ENTRY * PCGFF_LABEL_ENTRY;
	
	typedef struct _GFF_LIST_ENTRY
	{
		unsigned long Size;
//		unsigned long Indicies[ 0 ];
	} GFF_LIST_ENTRY, * PCFF_LIST_ENTRY;

	typedef const struct _GFF_LIST_ENTRY * PCGFF_LIST_ENTRY;
	
	typedef struct _GFF_CEXOLOCSUBSTRING_ENTRY
	{
		unsigned long StringID; // LanguageID << 1 | Gender
		unsigned long StringLength;
//		char          String[ 0 ];
	} GFF_CEXOLOCSUBSTRING_ENTRY, * PGFF_CEXOLOCSUBSTRING_ENTRY;

	typedef const struct _GFF_CEXOLOCSUBSTRING_ENTRY * PCGFF_CEXOLOCSUBSTRING_ENTRY;
	
	typedef struct _GFF_CEXOLOCSTRING_ENTRY
	{
		unsigned long              Length;   // Not inclusive of the length field
		unsigned long              StringRef;
		unsigned long              StringCount;
//		GFF_CEXOLOCSUBSTRING_ENTRY SubStrings[ 0 ];
	} GFF_CEXOLOCSTRING_ENTRY, * PGFF_CEXOLOCSTRING_ENTRY;

	typedef const struct _GFF_CEXOLOCSTRING_ENTRY * PCGFF_CEXOLOCSTRING_ENTRY;
	
//#include <poppack.h>

private:

public:

	friend class GffStruct;

	//
	// Define the GFF structure object, used to access structures in a GFF
	// file.  The GffStruct represents the primary mechanism for navigating the
	// GFF hierarchy.
	//

	class GffStruct
	{

	public:

		inline
		GffStruct(
			)
		: m_Reader( NULL )
		{
			ZeroMemory( &m_StructEntry, sizeof( m_StructEntry ) );
		}

		inline
		GffStruct(
			 const GffFileReader * Reader,
			 PCGFF_STRUCT_ENTRY StructEntry
			)
		: m_Reader( Reader ),
		  m_StructEntry( *StructEntry )
		{
		}

		inline
		~GffStruct(
			)
		{
		}

		//
		// Return the underlying reader object.
		//

		inline
		const GffFileReader *
		GetReader(
			) const
		{
			return m_Reader;
		}

		//
		// Return the type of this structure.
		//

		inline
		unsigned long
		GetType(
			) const
		{
			return m_StructEntry.Type;
		}

		//
		// Return the count of fields in the structure.
		//

		inline
		FIELD_INDEX
		GetFieldCount(
			) const
		{
			return m_StructEntry.FieldCount;
		}

		//
		// Return the type of a field.
		//

		inline
		bool
		GetFieldType(
			 const char * FieldName,
			 GFF_FIELD_TYPE & FieldType
			) const
		{
			GFF_FIELD_ENTRY FieldEntry;

			if (!GetFieldByName( FieldName, FieldEntry ))
				return false;

			FieldType = (GFF_FIELD_TYPE) FieldEntry.Type;

			return true;
		}

		bool
		GetFieldType(
			 FIELD_INDEX FieldIndex,
			 GFF_FIELD_TYPE & FieldType
			) const;

		//
		// Return the name of a field.
		//

		bool
		GetFieldName(
			 FIELD_INDEX FieldIndex,
			 std::string & FieldName
			) const;

		//
		// Return the index of a field.
		//

		inline
		bool
		GetFieldIndex(
			 const char * FieldName,
			 FIELD_INDEX & FieldIndex
			) const
		{
			return GetFieldIndexByName( FieldName, FieldIndex );
		}

		//
		// Return the raw data of a field by index.
		//

		bool
		GetFieldRawData(
			 FIELD_INDEX FieldIndex,
			 std::vector< unsigned char > & FieldData,
			 std::string & FieldName,
			 GFF_FIELD_TYPE & FieldType,
			 bool & ComplexField
			) const;

		//
		// Data field primitive accessors.  These routines pull data out of a
		// GFF structure.  The data type is required to exactly match for the
		// routine to succeed.  No data type accessor routine throws an
		// exception on failure; all return false.
		//

		inline
		bool
		GetBYTE(
			 const char * FieldName,
			 uint8_t & Data
			) const
		{
			return GetSmallFieldByName( GFF_BYTE, FieldName, Data );
		}

		inline
		bool
		GetBYTEAsBool(
			 const char * FieldName,
			 bool & Data
			) const
		{
			uint8_t b;

			if (!GetBYTE( FieldName, b ))
				return false;

			Data = (b ? 1 : 0);

			return true;
		}

		inline
		bool
		GetCHAR(
			 const char * FieldName,
			 int8_t & Data
			) const
		{
			return GetSmallFieldByName( GFF_CHAR, FieldName, Data );
		}

		inline
		bool
		GetWORD(
			 const char * FieldName,
			 uint16_t & Data
			) const
		{
			return GetSmallFieldByName( GFF_WORD, FieldName, Data );
		}

		inline
		bool
		GetSHORT(
			 const char * FieldName,
			 int16_t & Data
			) const
		{
			return GetSmallFieldByName( GFF_SHORT, FieldName, Data );
		}

		inline
		bool
		GetDWORD(
			 const char * FieldName,
			 uint32_t & Data
			) const
		{
			return GetSmallFieldByName( GFF_DWORD, FieldName, Data );
		}

		inline
		bool
		GetDWORD(
			 const char * FieldName,
			 unsigned long & Data
			) const
		{
			return GetSmallFieldByName( GFF_DWORD, FieldName, Data );
		}

		inline
		bool
		GetINT(
			 const char * FieldName,
			 int32_t & Data
			) const
		{
			return GetSmallFieldByName( GFF_INT, FieldName, Data );
		}

		inline
		bool
		GetINTAsBool(
			 const char * FieldName,
			 bool & Data
			) const
		{
			int32_t i;

			if (!GetINT( FieldName, i ))
				return false;

			Data = (i ? 1 : 0);

			return true;
		}

		inline
		bool
		GetDWORD64(
			 const char * FieldName,
			 int32_t & Data
			) const
		{
			return GetLargeFieldByName( GFF_DWORD64, FieldName, Data );
		}

		inline
		bool
		GetINT64(
			 const char * FieldName,
			 int64_t & Data
			) const
		{
			return GetLargeFieldByName( GFF_INT64, FieldName, Data );
		}

		inline
		bool
		GetFLOAT(
			 const char * FieldName,
			 float & Data
			) const
		{
			return GetSmallFieldByName( GFF_FLOAT, FieldName, Data );
		}

		inline
		bool
		GetDOUBLE(
			 const char * FieldName,
			 double & Data
			) const
		{
			return GetLargeFieldByName( GFF_DOUBLE, FieldName, Data );
		}

		bool
		GetCExoString(
			 const char * FieldName,
			 std::string & Data
			) const;

		bool
		GetCExoStringAsResRef(
			 const char * FieldName,
			 NWN::ResRef32 & Data
			) const;

		bool
		GetResRef(
			 const char * FieldName,
			 NWN::ResRef32 & Data
			) const;

		bool
		GetCExoLocString(
			 const char * FieldName,
			 std::string & Data
			) const;

		bool
		GetVOID(
			 const char * FieldName,
			 std::vector< unsigned char > & Data
			) const;

		//
		// N.B.  Getting an empty field name that is a struct returns the
		//       current structure.  This is useful for operating on lists of
		//       complex types.
		//

		bool
		GetStruct(
			 const char * FieldName,
			 GffStruct & Struct
			) const;

		bool
		GetStructByIndex(
			 FIELD_INDEX FieldIndex,
			 GffStruct & Struct
			) const;

		//
		// N.B.  List elements span from 0...N.  One strategy is to simply call
		//       GetListElement with ever-increasing indicies until the call
		//       fails.
		//

		bool
		GetListElement(
			 const char * FieldName,
			 size_t Index,
			 GffStruct & Struct
			) const;

		bool
		GetListElementByIndex(
			 FIELD_INDEX FieldIndex,
			 size_t Index,
			 GffStruct & Struct
			) const;

		//
		// N.B.  Most Vectors are packed as a struct with "x", "y", "z" values.
		//

		inline
		bool
		GetVector3_DEPRECATED(
			 const char * FieldName,
			 NWN::Vector3 & v
			) const
		{
			return GetLargeFieldByName( GFF_VECTOR, FieldName, v );
		}

		//
		// Simple compound structure accessor helpers.
		//

		inline
		bool
		GetVector(
			 const char * FieldName,
			 NWN::Vector3 & v
			) const
		{
			GffStruct s;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetFLOAT( "x", v.x ))
				return false;
			if (!s.GetFLOAT( "y", v.y ))
				return false;
			if (!s.GetFLOAT( "z", v.z ))
				return false;

			return true;
		}

		inline
		bool
		GetQuaternion(
			 const char * FieldName,
			 NWN::Quaternion & q
			) const
		{
			GffStruct s;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetFLOAT( "x", q.x ))
				return false;
			if (!s.GetFLOAT( "y", q.y ))
				return false;
			if (!s.GetFLOAT( "z", q.z ))
				return false;
			if (!s.GetFLOAT( "w", q.w ))
				return false;

			return true;
		}

		inline
		bool
		GetColor(
			 const char * FieldName,
			 NWN::NWNCOLOR & c
			) const
		{
			GffStruct     s;
			unsigned char cc;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetBYTE( "r", cc ))
				return false;

			c.r = (float) cc / 255.0f;

			if (!s.GetBYTE( "g", cc ))
				return false;

			c.g = (float) cc / 255.0f;

			if (!s.GetBYTE( "b", cc ))
				return false;

			c.b = (float) cc / 255.0f;

			if (!s.GetBYTE( "a", cc ))
				return false;

			c.a = (float) cc / 255.0f;

			return true;
		}

		inline
		bool
		GetUVScroll(
			 const char * FieldName,
			 NWN::NWN2_UVScrollSet & UVScroll
			) const
		{
			GffStruct s;
			GffStruct Scroll;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetStruct( "UVScroll", Scroll ))
				return false;

			if (!Scroll.GetINTAsBool( "Scroll", UVScroll.Scroll ))
				return false;
			if (!Scroll.GetFLOAT( "U", UVScroll.U ))
				return false;
			if (!Scroll.GetFLOAT( "V", UVScroll.V ))
				return false;

			return true;
		}

		inline
		bool
		GetRawTintSet(
			 const char * FieldName,
			 NWN::NWN2_TintSet & TintSet
			) const
		{
			GffStruct         Tint;
			static const char TintNames[] = "123";

			if (!GetStruct( FieldName, Tint ))
				return false;

			for (size_t i = 0; i < 3; i += 1)
			{
				char      TintName[ 2 ];

				TintName[ 0 ] = TintNames[ i ];
				TintName[ 1 ] = '\0';

				if (!Tint.GetColor( TintName, TintSet.Colors[ i ] ))
					return false;
			}

			return true;
		}

		inline
		bool
		GetTintSet(
			 const char * FieldName,
			 NWN::NWN2_TintSet & TintSet
			) const
		{
			GffStruct s;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetRawTintSet( "Tint", TintSet ))
				return false;

			return true;
		}

		inline
		bool
		GetTintable(
			 const char * FieldName,
			 NWN::NWN2_TintSet & TintSet
			) const
		{
			GffStruct s;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetTintSet( "Tintable", TintSet ))
				return false;

			return true;
		}

		inline
		bool
		GetArmorAccessory(
			 const char * FieldName,
			 NWN::NWN2_ArmorAccessory & Accessory
			) const
		{
			GffStruct s;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetBYTE( "Accessory", Accessory.Variation ))
				return false;

			if (!s.GetTintable( NULL, Accessory.Tint ))
				return false;

			if (!s.GetUVScroll( NULL, Accessory.UVScroll ))
				return false;

			return true;
		}

		inline
		bool
		GetArmorPiece(
			 const char * FieldName,
			 NWN::NWN2_ArmorPiece & ArmorPiece
			) const
		{
			GffStruct s;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetBYTE( "Variation", ArmorPiece.Variation ))
				return false;
			if (!s.GetBYTE( "ArmorVisualType", ArmorPiece.VisualType ))
				return false;
			if (!s.GetRawTintSet( "ArmorTint", ArmorPiece.Tint ))
				return false;

			return true;
		}

		inline
		bool
		GetArmorPieceWithAccessories(
			 const char * FieldName,
			 NWN::NWN2_ArmorPieceWithAccessories & ArmorPiece
			) const
		{
			GffStruct           s;
			static const char * AccessoryNames[ NWN::Num_Accessories ] =
			{
				"ACLtShoulder",
				"ACRtShoulder",
				"ACLtBracer",
				"ACRtBracer",
				"ACLtElbow",
				"ACRtElbow",
				"ACLtArm",
				"ACRtArm",
				"ACLtHip",
				"ACRtHip",
				"ACFtHip",
				"ACBkHip",
				"ACLtLeg",
				"ACRtLeg",
				"ACLtShin",
				"ACRtShin",
				"ACLtKnee",
				"ACRtKnee",
				"ACLtFoot",
				"ACRtFoot",
				"ACLtAnkle",
				"ACRtAnkle"
			};

			if (!GetStruct( FieldName, s ))
				return false;

			for (size_t i = 0; i < NWN::Num_Accessories; i += 1)
			{
				try
				{
					if (!GetArmorAccessory( AccessoryNames[ i ], ArmorPiece.Accessories[ i ] ))
						return false;
				}
				catch (std::exception)
				{
					return false;
				}
			}

			if (!GetArmorPiece( FieldName, ArmorPiece ))
				return false;

			return true;
		}

		inline
		bool
		GetArmorAccessorySet(
			 const char * FieldName,
			 NWN::NWN2_ArmorAccessorySet & ArmorAccessorySet
			) const
		{
			GffStruct s;

			if (!GetStruct( FieldName, s ))
				return false;

			if (!s.GetArmorPieceWithAccessories( NULL, ArmorAccessorySet.Chest ))
				return false;

			ArmorAccessorySet.HasHelm   = (s.GetArmorPiece( "Helm", ArmorAccessorySet.Helm ) ? 1 : 0);
			ArmorAccessorySet.HasGloves = (s.GetArmorPiece( "Gloves", ArmorAccessorySet.Gloves ) ? 1 : 0);
			ArmorAccessorySet.HasBoots  = (s.GetArmorPiece( "Boots", ArmorAccessorySet.Boots ) ? 1 : 0);
			ArmorAccessorySet.HasBelt   = (s.GetArmorPiece( "Belt", ArmorAccessorySet.Belt ) ? 1 : 0);
			ArmorAccessorySet.HasCloak  = (s.GetArmorPiece( "Cloak", ArmorAccessorySet.Cloak ) ? 1 : 0);

			return true;
		}

		inline
		bool
		GetObjectLocation(
			 const char * FieldName,
			 NWN::ObjectLocation & Location
			) const
		{
			GffStruct s;

			if (!GetStruct( FieldName, s ))
				return false;

			Location.Area = NWN::INVALIDOBJID;

			if (!s.GetFLOAT( "XOrientation", Location.Orientation.x ))
				return false;
			if (!s.GetFLOAT( "YOrientation", Location.Orientation.y ))
				return false;

			Location.Orientation.z = 0.0f;

			if (!s.GetFLOAT( "XPosition", Location.Position.x ))
				return false;
			if (!s.GetFLOAT( "YPosition", Location.Position.y ))
				return false;
			if (!s.GetFLOAT( "ZPosition", Location.Position.z ))
				return false;

			return true;
		}

	private:

		//
		// Retrieve the field data for a field which fits within the
		// DataOrDataOffset block of a field descriptor.
		//

		template< typename T >
		bool
		GetSmallFieldByName(
			 GFF_FIELD_TYPE FieldType,
			 const char * FieldName,
			 T & Data
			) const
		{
			GFF_FIELD_ENTRY FieldEntry;

			if (!GetFieldByName( FieldName, FieldEntry ))
				return false;

			if (FieldEntry.Type != (unsigned long) FieldType)
				return false;

			memcpy( &Data, &FieldEntry.DataOrDataOffset, sizeof( T ) );

			return true;
		}

		//
		// Retrieve the field data for a field which is located within the
		// field data stream, but which has a simple (contiguous fixed size)
		// format.
		//

		template< typename T >
		bool
		GetLargeFieldByName(
			 GFF_FIELD_TYPE FieldType,
			 const char * FieldName,
			 T & Data
			) const
		{
			GFF_FIELD_ENTRY FieldEntry;

			if (!GetFieldByName( FieldName, FieldEntry ))
				return false;

			if (FieldEntry.Type != (unsigned long) FieldType)
				return false;

			return GetLargeFieldData( FieldEntry, &Data, sizeof( T ) );
		}

		//
		// Retrieve the raw data for a large field.  The data length is
		// assumed to be fixed.
		//

		bool
		GetLargeFieldData(
			 const GFF_FIELD_ENTRY & FieldEntry,
			 void * Data,
			 size_t Size,
			 size_t Offset = 0
			) const;

		//
		// Retrieve the raw data for a list index data field.  The data length
		// is assumed to be fixed.
		//

		bool
		GetListIndiciesData(
			 const GFF_FIELD_ENTRY & FieldEntry,
			 void * Data,
			 size_t Size,
			 size_t Offset = 0
			) const;

		//
		// Look up a field by name and return the field descriptor for it, else
		// return false on failure.
		//

		bool
		GetFieldByName(
			 const char * FieldName,
			 GFF_FIELD_ENTRY & FieldEntry
			) const;

		//
		// Look up a field by index and return the field descriptor for it,
		// else return false on failure.
		//

		bool
		GetFieldByIndex(
			 FIELD_INDEX Index,
			 GFF_FIELD_ENTRY & FieldEntry
			) const;

		//
		// Look up a field by name and return the field index for it, else return
		// false on failure.
		//

		bool
		GetFieldIndexByName(
			 const char * FieldName,
			 FIELD_INDEX & Index
			) const;

		//
		// Validate the length of a data stream read before performing it, so
		// that excessive buffer allocation for malformed files can be avoided.
		//

		bool
		ValidateFieldDataRange(
			 const GFF_FIELD_ENTRY & FieldEntry,
			 FIELD_DATA_INDEX DataOffset,
			 size_t Length
			) const;

		inline
		void
		SetReader(
			 GffFileReader * Reader
			)
		{
			m_Reader = Reader;
		}

		inline
		void
		SetStructEntry(
			 PCGFF_STRUCT_ENTRY StructEntry
			)
		{
			m_StructEntry = *StructEntry;
		}

		const GffFileReader * m_Reader;
		GFF_STRUCT_ENTRY      m_StructEntry;

		friend class GffFileReader;

	};

	//
	// Return the resource manager used to construct the reader.
	//

	inline
	ResourceManager &
	GetResourceManager(
		) const
	{
		return m_ResourceManager;
	}

private:

	//
	// Read a GFF field descriptor by index.
	//

	void
	GetFieldByIndex(
		 FIELD_INDEX FieldIndex,
		 GFF_FIELD_ENTRY & FieldEntry
		) const;

	//
	// Read a GFF label by index.
	//

	void
	GetLabelByIndex(
		 LABEL_INDEX LabelIndex,
		 std::string & Label
		) const;

	//
	// Read a GFF struct descriptor by index.
	//

	void
	GetStructByIndex(
		 STRUCT_INDEX StructIndex,
		 GFF_STRUCT_ENTRY & StructEntry
		) const;

	//
	// Compare field names.
	//

	bool
	CompareFieldName(
		 const GFF_FIELD_ENTRY & FieldEntry,
		 const char * Name
		) const;

	//
	// Look up a field by name.
	//

	bool
	GetFieldByName(
		 PCGFF_STRUCT_ENTRY Struct,
		 const char * FieldName,
		 GFF_FIELD_ENTRY & FieldEntry
		) const;

	//
	// Look up a field by structure index.
	//

	bool
	GetFieldByIndex(
		 PCGFF_STRUCT_ENTRY Struct,
		 FIELD_INDEX FieldIndex,
		 GFF_FIELD_ENTRY & FieldEntry
		) const;

	//
	// Look up the field id of field by name.
	//

	bool
	GetFieldIndexByName(
		 PCGFF_STRUCT_ENTRY Struct,
		 const char * FieldName,
		 FIELD_INDEX & FieldIndex
		) const;

	//
	// Return the type of a field.
	//

	bool
	GetFieldType(
		 PCGFF_STRUCT_ENTRY Struct,
		 FIELD_INDEX FieldIndex,
		 GFF_FIELD_TYPE & FieldType
		) const;

	//
	// Return the name of a field.
	//

	bool
	GetFieldName(
		 PCGFF_STRUCT_ENTRY Struct,
		 FIELD_INDEX FieldIndex,
		 std::string & FieldName
		) const;

	//
	// Return the raw data of a field by index.
	//

	bool
	GetFieldRawData(
		 PCGFF_STRUCT_ENTRY Struct,
		 FIELD_INDEX FieldIndex,
		 std::vector< unsigned char > & FieldData,
		 std::string & FieldName,
		 GFF_FIELD_TYPE & Type,
		 bool & ComplexField
		) const;

	//
	// Retrieve a section of data from the field data stream.
	//

	bool
	ReadFieldData(
		 FIELD_DATA_INDEX FieldDataIndex,
		 void * Buffer,
		 size_t Length
		) const;

	//
	// Retrieve a section of list index data from the list index stream.
	//

	bool
	ReadListIndicies(
		 LIST_INDICIES_INDEX ListIndiciesIndex,
		 void * Buffer,
		 size_t Length
		) const;

	//
	// Validate the length of a data stream read before performing it, so that
	// excessive buffer allocaiton for malformed files can be avoided.
	//

	bool
	ValidateFieldDataRange(
		 FIELD_DATA_INDEX FieldDataIndex,
		 size_t Length
		) const;

	//
	// Return the size and data pointer of a field.  If the field is a small
	// field then the size is returned.  Otherwise if the field is a large
	// field then zero is returned for the size.
	//
	// If the field type was unrecognized, or the field has no actual data
	// (such as a list or a structure), then false is returned.
	//

	bool
	GetFieldSizeAndData(
		 const GFF_FIELD_ENTRY & FieldEntry,
		 const void * * FieldData,
		 size_t * FieldDataLength
		) const;

//	//
//	// Retrieve a talk string from the resource manager talk table.
//	//
//
//	bool
//	GetTalkString(
//		 unsigned long StrRef,
//		 std::string & Str
//		) const;

	//
	// Convert a resref to a string.
	//

	NWN::ResRef32
	ResRef32FromStr(
		 const std::string & Str
		) const;

	//
	// Return the underlying FileWrapper for use by the GffStruct object.
	//

	inline
	volatile FileWrapper *
	GetFileWrapper(
		) const
	{
		return &m_FileWrapper;
	}

	//
	// Define file book-keeping data.
	//

	HANDLE                m_File;
	unsigned long         m_FileSize;
	mutable FileWrapper   m_FileWrapper;
	GFF_HEADER            m_Header;

	GFF_LANGUAGE          m_Language; // Default LocString language code

	//
	// Define the root structure.  We cache it in memory for ease of use.
	//

	GffStruct             m_RootStruct;

	//
	// Resource manager back-link, for TLK lookup.
	//

	ResourceManager     & m_ResourceManager;

};

#endif
