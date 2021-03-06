/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/LogicalTimeFactory.h
***********************************************************************/

#ifndef RTI_LogicalTimeFactory_h
#define RTI_LogicalTimeFactory_h

// ****************************************************************
// ********************** Adjusted for CERTI **********************
// ****************************************************************
// This file is one of the SISO HLA 1516 header files that was edited
// by CERTI for compilation. By default, there exists a circular
// dependency between the RTI library (provided by CERTI) and the
// LogicalTime implementation (to be provided by the federate).
// In order to break this dependency some minor changes have been
// applied: The LogicalTime, LogicalTimeInterval and 
// LogicalTimeFactory classes are now exported by the LogicalTime 
// implementation. All three classes have been given an inline (empty)
// destructor.
// While these changes may break (direct) DLL compatibility, they
// greatly ease the implementation of the RTI1516 library for CERTI.
// ****************************************************************
// ********************** Adjusted for CERTI **********************
// ****************************************************************


namespace rti1516e
{
  class LogicalTime;
  class LogicalTimeInterval;
}

#include <RTI/SpecificConfig.h>
#include <RTI/Exception.h>
#include <string>
#include <memory>

// LogicalTimeFactory is used by the RTI to construct instances of classes
// derived from LogicalTime and LogicalTimeInterval.  A federation is responsible
// for providing a fedtime library that includes one or more subclasses
// of LogicalTime and LogicalTimeInterval, one or more subclasses of LogicalTimeFactory
// (which is used to create instances of those LogicalTime and LogicalTimeInterval
// subclasses), and a single implementation of 
// LogicalTimeFactoryFactory::createLogicalTimeFactory.  This static function should
// choose a LogicalTimeFactory based on the string identifier passed as an argument,
// and return an instance of that kind of factory.  The RTI will call this function to
// obtain a LogicalTimeFactory for a federation, and then will use that factory to create
// any instances of LogicalTime or LogicalTimeInterval that it needs.

namespace rti1516e
{
  class RTI_EXPORT_FEDTIME LogicalTimeFactory
  {
  public:
    virtual
    ~LogicalTimeFactory()
      throw () { };
    
    // Returns a LogicalTime with a value of "initial"
    virtual
    std::auto_ptr< LogicalTime >
    makeLogicalTime()
      throw (InternalError) = 0;
    
    // Returns a LogicalTimeInterval with a value of "zero"
    virtual 
    std::auto_ptr< LogicalTimeInterval >
    makeLogicalTimeInterval() 
      throw (InternalError) = 0;
  };
}


namespace rti1516e

{  
  class RTI_EXPORT_FEDTIME LogicalTimeFactoryFactory
  {
  public:

    // The name is used to choose among several LogicalTimeFactories that might
    // be present in the fedtime library.  Each federation chooses its
    // implementation by passing the appropriate name to createFederationExecution.
    // If the supplied name is the empty string, a default LogicalTimeFactory is
    // returned.  If the supplied implementation name does not match any name 
    // supported by the library, then a NULL pointer is returned. 
    static std::auto_ptr< LogicalTimeFactory > 
       makeLogicalTimeFactory(std::wstring const & implementationName);
  };
}

#endif // RTI_LogicalTimeFactory_h
