// -*- mode:C++ ; tab-width:4 ; c-basic-offset:4 ; indent-tabs-mode:nil -*-
// ----------------------------------------------------------------------------
// CERTI - HLA RunTime Infrastructure
// Copyright (C) 2003  ONERA
//
// This file is part of CERTI-libCERTI
//
// CERTI-libCERTI is free software ; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation ; either version 2 of
// the License, or (at your option) any later version.
//
// CERTI-libCERTI is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY ; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program ; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA
//
// $Id: XmlParser2000.hh,v 1.0 2015/02/10 10:45:20 JLB Exp $
// ----------------------------------------------------------------------------

#ifndef _CERTI_XML_PARSER_2000_HH
#define _CERTI_XML_PARSER_2000_HH

// Project
#include "RootObject.hh"
#include "ObjectClass.hh"
#include "Interaction.hh"
#include "XmlParser.hh"

// Libraries
#ifdef HAVE_XML
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#endif

// Standard libraries
#include <string>

namespace certi {

/**
 * The CERTI 2000 XML federation Object Model parser.
 */
class CERTI_EXPORT XmlParser2000 : public XmlParser {
public:
	
	/**
	 * Build a parser.
	 * @param root the root object of the FOM.
	 */
	XmlParser2000(RootObject* root);
	
	virtual ~XmlParser2000() ;

	/** 
	 * Main method to parse .xml FOM file
	 * @param[in] pathToXmlFile the path to the XML file.
	 * @return the RootObject resulting from the parse. 
	 */	   
    //RootObject* parse(std::string pathToXmlFile);

	/**
	 * ParseNTOS get name transportation order and space
	 * @param[in] the current node
	 * @param[out] name transportation order and space
	 * @return nothing
	 */
    virtual void parseNTOS(xmlNodePtr cur, HLAntos_t  *ntos_p);

    /**
	 * get the node name
	 * @param[in] current node
	 * @return the name
	 */
    virtual xmlChar * getName(xmlNodePtr cur);
};

} // namespace certi

#endif // _CERTI_XML_PARSER_HH

// $Id: XmlParser2000.hh,v 3.12 2007/08/31 13:43:20 erk Exp $
