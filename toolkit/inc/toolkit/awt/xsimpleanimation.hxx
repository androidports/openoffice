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


#ifndef TOOLKIT_AWT_XSIMPLEANIMATION_HXX
#define TOOLKIT_AWT_XSIMPLEANIMATION_HXX

#include <toolkit/awt/vclxwindow.hxx>
#include <toolkit/helper/listenermultiplexer.hxx>
#include <cppuhelper/implbase1.hxx>
#include <comphelper/uno3.hxx>
#include <com/sun/star/awt/XSimpleAnimation.hpp>

#include <boost/scoped_ptr.hpp>

//........................................................................
namespace toolkit
{
//........................................................................

	//====================================================================
	//= XSimpleAnimation
	//====================================================================
    typedef ::cppu::ImplInheritanceHelper1  <   VCLXWindow
                                            ,   ::com::sun::star::awt::XSimpleAnimation
                                            >   XSimpleAnimation_Base;

    class XSimpleAnimation : public XSimpleAnimation_Base
	{
    public:
        XSimpleAnimation();

    protected:
        ~XSimpleAnimation();

        // XSimpleAnimation
        virtual void SAL_CALL start() throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL stop() throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setImageList( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::graphic::XGraphic > >& ImageList )
                                            throw (::com::sun::star::uno::RuntimeException);
	    // VclWindowPeer
        virtual void SAL_CALL setProperty( const ::rtl::OUString& PropertyName, const ::com::sun::star::uno::Any& Value ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Any SAL_CALL getProperty( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::uno::RuntimeException);

    private:
        XSimpleAnimation( const XSimpleAnimation& );            // never implemented
        XSimpleAnimation& operator=( const XSimpleAnimation& ); // never implemented
	};

//........................................................................
} // namespacetoolkit
//........................................................................

#endif // TOOLKIT_INC_TOOLKIT_AWT_XSIMPLEANIMATION_HXX

