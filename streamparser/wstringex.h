#pragma once

#include <string>
#include <algorithm>
#include <atlbase.h>
using namespace std;

class wstringex 
{
public:	
	wstring m_sz;
	
	wstringex() 
	{
	}
	
	wstringex( const wchar_t* sz )
	:m_sz(sz)
	{
	}
		
	wstringex( const wstringex& sz)
	{
		m_sz= sz.m_sz;
	}
	
	wstringex ( const wstring& sz )
	{
		m_sz= sz;
	}
	
	wstringex& operator =( const wstringex& sz )
	{
		if( &sz != this )
			m_sz= sz.m_sz;
		return (*this );
	}
	
	wstringex& operator= ( const wstring& sz )
	{
		m_sz= sz;
		return (*this);
	}

	wstring* operator -> ()
	{ 
		return &m_sz; 
	}

	const wstring* operator -> () const 
	{ 
		return &m_sz; 
	}

	operator wstring () const
	{
		return m_sz;
	}

	wstringex& operator += (const wstringex& wstr)
	{
		m_sz += wstr.m_sz;
		return (*this);
	}

	bool format( const wchar_t* szformat, ... )
	{
		va_list args;
		va_start( args, szformat );
		int len = _vscwprintf( szformat, args )+ 1;
		if( len > 0 )
		{
			wchar_t* buffer = new wchar_t[ len]; 
			if( NULL != buffer )
			{
				vswprintf_s( buffer, len, szformat, args );
				m_sz = buffer;
				delete [] buffer;
				return true;
			}
		}
		return false;
	}

	void trim()
	{
		size_t pos = m_sz.find_last_not_of(' ');
		if(pos != string::npos) 
		{
			m_sz.erase(pos + 1);
			pos = m_sz.find_first_not_of(' ');
			if(pos != string::npos) 
				m_sz.erase(0, pos);
		}
		else
		{
			m_sz.erase(m_sz.begin(), m_sz.end());	
		}
	}

	void makeupper()
	{
		transform(m_sz.begin(), m_sz.end(), m_sz.begin(), toupper);
	}

	void makelower()
	{
		transform(m_sz.begin(), m_sz.end(), m_sz.begin(), tolower);
	}

	wchar_t& operator[] ( size_t nindex )
	{
		return m_sz[nindex];
	}

	wchar_t operator[] ( size_t nindex ) const
	{
		return m_sz[nindex];
	}

	int compareNoCase( const wchar_t* sz )const
	{
		return _tcsicmp( m_sz.c_str(), sz );
	}

	BSTR allocSysString()
	{
		return SysAllocString( m_sz.c_str() );
	}

	wstring tokenize( wchar_t token, size_t& pos )
	{
		if( pos < 0 || pos > m_sz.length() )
		{
		#ifdef _WIN64
			pos = 0xFFFFFFFFFFFFFFFF;
		#else
			pos = 0xFFFFFFFF;
		#endif
			return L"";
		}

		size_t found = m_sz.find( token, pos );
		if( -1 != found )
		{
			wstring sztoken= m_sz.substr(pos, found-pos );
			pos = found+1;
			return sztoken;
		}
		wstring sztoken = m_sz.substr(pos, m_sz.length()-pos);
		#ifdef _WIN64
			pos = 0xFFFFFFFFFFFFFFFF;
		#else
			pos = 0xFFFFFFFF;
		#endif
		return sztoken;
	}
};

