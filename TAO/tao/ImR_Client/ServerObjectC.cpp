// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// be\be_codegen.cpp:302


#include "ServerObjectC.h"
#include "tao/CDR.h"
#include "tao/Exception_Data.h"
#include "tao/Invocation_Adapter.h"
#include "tao/Object_T.h"
#include "tao/Basic_Arguments.h"
#include "ace/OS_NS_string.h"

#if defined (__BORLANDC__)
#pragma option -w-rvl -w-rch -w-ccc -w-aus -w-sig
#endif /* __BORLANDC__ */

#if !defined (__ACE_INLINE__)
#include "ServerObjectC.inl"
#endif /* !defined INLINE */

// TAO_IDL - Generated from
// be\be_visitor_arg_traits.cpp:69

// Arg traits specializations.
namespace TAO
{
}


// TAO_IDL - Generated from
// be\be_visitor_interface/interface_cs.cpp:60

// Traits specializations for ImplementationRepository::ServerObject.

ImplementationRepository::ServerObject_ptr
TAO::Objref_Traits<ImplementationRepository::ServerObject>::duplicate (
    ImplementationRepository::ServerObject_ptr p
  )
{
  return ImplementationRepository::ServerObject::_duplicate (p);
}

void
TAO::Objref_Traits<ImplementationRepository::ServerObject>::release (
    ImplementationRepository::ServerObject_ptr p
  )
{
  CORBA::release (p);
}

ImplementationRepository::ServerObject_ptr
TAO::Objref_Traits<ImplementationRepository::ServerObject>::nil (void)
{
  return ImplementationRepository::ServerObject::_nil ();
}

CORBA::Boolean
TAO::Objref_Traits<ImplementationRepository::ServerObject>::marshal (
    ImplementationRepository::ServerObject_ptr p,
    TAO_OutputCDR & cdr
  )
{
  return CORBA::Object::marshal (p, cdr);
}

// Function pointer for collocation factory initialization.
TAO::Collocation_Proxy_Broker * 
(*ImplementationRepository__TAO_ServerObject_Proxy_Broker_Factory_function_pointer) (
    CORBA::Object_ptr obj
  ) = 0;

// TAO_IDL - Generated from
// be\be_visitor_operation/operation_cs.cpp:78

void ImplementationRepository::ServerObject::ping (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  if (!this->is_evaluated ())
    {
      ACE_NESTED_CLASS (CORBA, Object)::tao_object_initialize (this);
    }
  
  if (this->the_TAO_ServerObject_Proxy_Broker_ == 0)
    {
      ImplementationRepository_ServerObject_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "ping",
      4,
      this->the_TAO_ServerObject_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0 ACE_ENV_ARG_PARAMETER);
  ACE_CHECK;
}

// TAO_IDL - Generated from
// be\be_visitor_operation/operation_cs.cpp:78

void ImplementationRepository::ServerObject::shutdown (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  if (!this->is_evaluated ())
    {
      ACE_NESTED_CLASS (CORBA, Object)::tao_object_initialize (this);
    }
  
  if (this->the_TAO_ServerObject_Proxy_Broker_ == 0)
    {
      ImplementationRepository_ServerObject_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "shutdown",
      8,
      this->the_TAO_ServerObject_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0 ACE_ENV_ARG_PARAMETER);
  ACE_CHECK;
}

ImplementationRepository::ServerObject::ServerObject (void)
 : the_TAO_ServerObject_Proxy_Broker_ (0)
{
  this->ImplementationRepository_ServerObject_setup_collocation ();
}

void
ImplementationRepository::ServerObject::ImplementationRepository_ServerObject_setup_collocation ()
{
  if (::ImplementationRepository__TAO_ServerObject_Proxy_Broker_Factory_function_pointer)
    {
      this->the_TAO_ServerObject_Proxy_Broker_ =
        ::ImplementationRepository__TAO_ServerObject_Proxy_Broker_Factory_function_pointer (this);
    }
}

ImplementationRepository::ServerObject::~ServerObject (void)
{}

void 
ImplementationRepository::ServerObject::_tao_any_destructor (void *_tao_void_pointer)
{
  ServerObject *_tao_tmp_pointer =
    static_cast<ServerObject *> (_tao_void_pointer);
  CORBA::release (_tao_tmp_pointer);
}

ImplementationRepository::ServerObject_ptr
ImplementationRepository::ServerObject::_narrow (
    CORBA::Object_ptr _tao_objref
    ACE_ENV_ARG_DECL
  )
{
  return
    TAO::Narrow_Utils<ServerObject>::narrow (
        _tao_objref,
        "IDL:ImplementationRepository/ServerObject:1.0",
        ImplementationRepository__TAO_ServerObject_Proxy_Broker_Factory_function_pointer
        ACE_ENV_ARG_PARAMETER
      );
}

ImplementationRepository::ServerObject_ptr
ImplementationRepository::ServerObject::_unchecked_narrow (
    CORBA::Object_ptr _tao_objref
    ACE_ENV_ARG_DECL
  )
{
  return
    TAO::Narrow_Utils<ServerObject>::unchecked_narrow (
        _tao_objref,
        "IDL:ImplementationRepository/ServerObject:1.0",
        ImplementationRepository__TAO_ServerObject_Proxy_Broker_Factory_function_pointer
        ACE_ENV_ARG_PARAMETER
      );
}

ImplementationRepository::ServerObject_ptr
ImplementationRepository::ServerObject::_duplicate (ServerObject_ptr obj)
{
  if (! CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }
  
  return obj;
}

void
ImplementationRepository::ServerObject::_tao_release (ServerObject_ptr obj)
{
  CORBA::release (obj);
}

CORBA::Boolean
ImplementationRepository::ServerObject::_is_a (
    const char *value
    ACE_ENV_ARG_DECL
  )
{
  if (
      !ACE_OS::strcmp (
          value,
          "IDL:ImplementationRepository/ServerObject:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:omg.org/CORBA/Object:1.0"
        )
    )
    {
      return true; // success using local knowledge
    }
  else
    {
      return this->ACE_NESTED_CLASS (CORBA, Object)::_is_a (
          value
          ACE_ENV_ARG_PARAMETER
        );
    }
}

const char* ImplementationRepository::ServerObject::_interface_repository_id (void) const
{
  return "IDL:ImplementationRepository/ServerObject:1.0";
}

CORBA::Boolean
ImplementationRepository::ServerObject::marshal (TAO_OutputCDR &cdr)
{
  return (cdr << this);
}

// TAO_IDL - Generated from
// be\be_visitor_interface/cdr_op_cs.cpp:63

CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const ImplementationRepository::ServerObject_ptr _tao_objref
  )
{
  CORBA::Object_ptr _tao_corba_obj = _tao_objref;
  return (strm << _tao_corba_obj);
}

CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    ImplementationRepository::ServerObject_ptr &_tao_objref
  )
{
  CORBA::Object_var obj;
  
  if (!(strm >> obj.inout ()))
    {
      return false;
    }
  
  typedef ::ImplementationRepository::ServerObject RHS_SCOPED_NAME;
  
  // Narrow to the right type.
  _tao_objref =
    TAO::Narrow_Utils<RHS_SCOPED_NAME>::unchecked_narrow (
        obj.in (),
        ImplementationRepository__TAO_ServerObject_Proxy_Broker_Factory_function_pointer
      );
    
  return 1;
}

// TAO_IDL - Generated from
// be\be_visitor_root/root.cpp:1521

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

  template class
    TAO::Objref_Traits<
        ImplementationRepository::ServerObject
      >;

  template class
    TAO_Objref_Var_T<
        ImplementationRepository::ServerObject
      >;
  
  template class
    TAO_Objref_Out_T<
        ImplementationRepository::ServerObject
      >;

  template class
    TAO::Narrow_Utils<
        ImplementationRepository::ServerObject
      >;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

# pragma instantiate \
    TAO::Objref_Traits< \
        ImplementationRepository::ServerObject \
      >

# pragma instantiate \
    TAO_Objref_Var_T< \
        ImplementationRepository::ServerObject
      >
  
# pragma instantiate \
    TAO_Objref_Out_T< \
        ImplementationRepository::ServerObject
      >

# pragma instantiate \
    TAO::Narrow_Utils< \
        ImplementationRepository::ServerObject \
      >

#endif /* !ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */ 
