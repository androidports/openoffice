/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


#ifndef HELPDATAFILEPROXY_DB_HXX_
#define HELPDATAFILEPROXY_DB_HXX_

#include "com/sun/star/ucb/XSimpleFileAccess.hpp"

#include <hash_map>
#include <rtl/string.hxx>

namespace helpdatafileproxy {

    namespace hdf_internal
    {
        class Noncopyable
        {
            // not implemented
            Noncopyable(const Noncopyable&);
            void operator=(const Noncopyable&);
        protected:
            Noncopyable() {}
            ~Noncopyable() {}
        };
    }

	class HDFData
	{
		friend class		Hdf;

		int					m_nSize;
		char*				m_pBuffer;

		void copyToBuffer( const char* pSrcData, int nSize );

	public:
		HDFData( void )
			: m_nSize( 0 )
			, m_pBuffer( NULL )
		{}
		~HDFData()
			{ delete [] m_pBuffer; }

  	    int getSize() const
			{ return m_nSize; }
  	    const char* getData() const
			{ return m_pBuffer; }
	};

	struct eq
	{
		bool operator()( const rtl::OString& rKey1, const rtl::OString& rKey2 ) const
			{ return rKey1.compareTo( rKey2 ) == 0; }
	};

	struct ha
	{
		size_t operator()( const rtl::OString& rName ) const
			{ return rName.hashCode(); }
	};

	typedef std::hash_map< rtl::OString,std::pair<int,int>,ha,eq >	StringToValPosMap;
	typedef std::hash_map< rtl::OString,rtl::OString,ha,eq >		StringToDataMap;

	class Hdf : hdf_internal::Noncopyable
	{
		rtl::OUString		m_aFileURL;
		StringToDataMap*	m_pStringToDataMap;
		StringToValPosMap*	m_pStringToValPosMap;
		com::sun::star::uno::Reference< com::sun::star::ucb::XSimpleFileAccess >
							m_xSFA;

		com::sun::star::uno::Sequence< sal_Int8 >
							m_aItData;
		const char*			m_pItData;
		int					m_nItRead;
		int					m_iItPos;

		bool implReadLenAndData( const char* pData, int& riPos, HDFData& rValue );

	public:
        //HDFHelp must get a fileURL which can then directly be used by simple file access.
        //SimpleFileAccess requires file URLs as arguments. Passing file path may work but fails
        //for example when using long file paths on Windows, which start with "\\?\"
		Hdf( const rtl::OUString& rFileURL,
			com::sun::star::uno::Reference< com::sun::star::ucb::XSimpleFileAccess > xSFA )
				: m_aFileURL( rFileURL )
				, m_pStringToDataMap( NULL )
				, m_pStringToValPosMap( NULL )
				, m_xSFA( xSFA )
				, m_pItData( NULL )
				, m_nItRead( -1 )
				, m_iItPos( -1 )
		{
            OSL_ASSERT(!rFileURL.compareTo(rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("file:")), 5));
        }
		~Hdf()
			{ releaseHashMap(); }

		void createHashMap( bool bOptimizeForPerformance = false );
		void releaseHashMap( void );

		bool getValueForKey( const rtl::OString& rKey, HDFData& rValue );

		bool startIteration( void );
		bool getNextKeyAndValue( HDFData& rKey, HDFData& rValue );
		void stopIteration( void );
	};
}

#endif

