// $Id$

// ===========================================================
//
// @file CIAO_Glue_Session_Template.h
//
//    This is a pseudo-meta generic servant implementations template
//    for CCIDL.  It demonstrates how a servant implementation for a
//    session component should look like.
//
//    The generated filename for files using this template shoule be
//       [idl-basename]GS.h         GS --> GlueSession
//
// @author Nanbor Wang <nanbor@cs.wustl.edu>
//
// ===========================================================

#ifndef CIAO_GLUE_SESSION_[idl-basename]GS_H
#define CIAO_GLUE_SESSION_[idl-basename]GS_H
#include "ace/pre.h"

#include "[idl-name]S.h"        // Source in the skeletons for component
                                // client-view equivalent interfaces
#include "[idl-name]EC.h"       // Source in the executor mapping
                                // that component implementations use
#include "ciao/Container_Base.h" //Source in the container interface definitions
#include "[SERVANT]_export.h"   // Generated export decl

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#if component is defined withing a [module name]
namespace CIAO_GLUE_[module_name]
{
#else
namespace CIAO_GLUE
{
#endif

  //////////////////////////////////////////////////////////////////
  // Facet Glue Code implementation
  // @@ We are assuming that these facets are declared under the same
  //    module as the component (thus, we are placing this glue code
  //    here under the same namespace.  If they are not, we will
  //    either be generating them in separate namespaces, or include
  //    some other CIDL generated files to get the glue code
  //    implementation.

#foreach [facet type] in (all facet interface types in the original IDL)
  class [SERVANT]_Export [facet type]_Servant :
    : public virtual POA_[facet type], // full skeleton name here
      public virtual PortableServer::RefCountServantBase
  {
  public:
    // Constructor and destructor.
    [facet type]_Servant (CCM_[facet type]_ptr executor);
    ~[facet tyep]_Servant ();

# foreach [operation] in (all facet operations)
    // Generate operation decls.
# end foreach [operation]

  protected:
    CCM_[facet type]_var executor_;
  };
#end foreach [facet type]

  //////////////////////////////////////////////////////////////////
  // EventConsumer Glue Code implementation
  // @@ We are assuming that these consumers are declared under the same
  //    module as the component (thus, we are placing this glue code
  //    here under the same namespace.  If they are not, we will
  //    either be generating them in separate namespaces, or include
  //    some other CIDL generated files to get the glue code
  //    implementation.

#foreach [event type] in (all eventtype-s defined in the original IDL)
  class [SERVANT]_Export [event type]Consumer_Servant :
    : public virtual POA_[event type]Consumer, // full skeleton name here
      public virtual PortableServer::RefCountServantBase
  {
  public:
    // Constructor and destructor.
    [event type]Consumer_Servant (CCM_[event type]Consumer_ptr executor);
    ~[event type]Consumer_Servant ();

# foreach [type] in ([event type] and all its parent eventtype, if any)
    void push_[type] ([type]_ptr evt
                      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
# end [type]

    // Inherit from ::Compopnents::EventBConsumerBase
    void push_event (EventBase_ptr ev
                     ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       ::Components::BadEventType));


  protected:
    CCM_[event type]Consumer_var executor_;
  };
#end foreach [facet name]


  //////////////////////////////////////////////////////////////////
  // Component specific context implementation
  class [SERVANT]_Export [component name]_Context :
    public virtual CCM_[component name]_Context
  // @@ The following line is causing compiler to barf, what gives?
  //    It looks like we need to overwrite _repository_id and
  //    _tao_QueryInterface operations here.
  //  , public virtual ::Components::SessionContext
  {
  public:
    // We will allow the the servant glue code we generate to access
    // our states.
    friend class [component name]_Servant;

    // Ctor.
    [component name]_Context ();

    // Dtor.
    virtual ~[component name]_Context ();

    // We need to overwrite the following method to avoid ambiguity
    // This is strange, but thankfully, this is generated code so it's
    // okay (?) to mess with this.

    virtual void *_tao_QueryInterface (ptr_arith_t type);

    virtual const char* _interface_repository_id (void) const;

    // Operations for [component name] event source, and
    // receptacles defined in CCM_[component name]_Context.

#foreach [receptacle name] with [uses type] in (list of all 'uses' interfaces) generate:
# if [receptacle name] is a simplex receptacle ('uses')
    [uses type] get_connection_[receptacle name] ();
# else ([receptacle name] is a multiplex ('uses multiple') receptacle)
    // [receptacle name]Connections typedef'ed as a sequence of
    // struct [receptacle name]Connection.
    [receptacle name]Connections get_connections_[receptacle name] ();
# endif [receptacle name]
#end foreach [receptacle name] with [uses type]

#foreach [event name] with [eventtype] in (list of all event sources) generate:
    void push_[event name] (in [eventtype] ev);
#end foreach [event name] with [eventtype]

    // Operations for ::Components::CCMContext
    virtual ::Components::Principal_ptr get_caller_principal (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::Components::CCMHome_ptr get_CCM_home (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual CORBA::Boolean get_rollback_only (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::IllegalState));
    virtual ::Components::Transaction::UserTransaction_ptr get_user_transaction (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::IllegalState));
    virtual CORBA::Boolean is_caller_in_role (const char * role
                                              ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual void set_rollback_only (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::IllegalState));

    // Operations for ::Components::SessionContext interface
    virtual CORBA::Object_ptr get_CCM_object (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::IllegalState));
  protected:
    // We need to generate, in protected section, stuff that manage
    // connections and consumers of this component.

#foreach [receptacle name] with [uses type] in (list of all 'uses' interfaces) generate:
# if [receptacle name] is a simplex receptacle ('uses')
    // Simplex [receptacle name] connection management operations
    void connect_[receptacle name] (in [uses type] c)
      raises (::Components::AlreadyConnected,
              ::Components::InvalidConnection);
    [uses type] disconnect_[receptacle name] ()
      raises (::Components::NoConnection);

    // Simplex [receptacle name] connection
    [uses type]_var ciao_uses_[receptacle name]_;

# else ([receptacle name] is a multiplex ('uses multiple') receptacle)
    // Multiplex [receptacle name] connection management operations
    ::Components::Cookie_ptr connect_[receptacle name] (in [uses type] c)
      raises (::Components::ExceedConnectionLimit,
              ::Components::InvalidConnection);
    [uses type] disconnect_[receptacle name] (in ::Components::Cookie_ptr ck)
      raises (::Components::InvalidConnection);

    // Multiplex [receptacle name] connections

    CIAO::Active_Objref_Map ciao_muses_[receptacle name]_;
# endif [receptacle name]
#end foreach [receptacle name] with [uses type]

    // Operations for emits interfaces.
#foreach [emit name] with [eventtype] in (list of all emitters) generate:
    void connect_[emit name] (in [eventtype]Consumer_ptr c)
      raises (::Components::AlreadyConnected);

    [eventtype]Consumer_ptr disconnect_[emit name] ()
      raises (::Components::NoConnection);

    [eventtype]Consumer_var ciao_emits_[emit name]_consumer_;
#end foreach [emit name] with [eventtype]

    // Operations for publishes interfaces.
#foreach [publish name] with [eventtype] in (list of all publishers) generate:
      ::Components::Cookie_ptr
      subscribe_[publish name] ([eventtype]Consumer_ptr c)
        raises (::Components::ExceededConnectionLimit);

      [eventtype]Consumer_ptr
      unsubscribe_[publish name] (::Components::Cookie_ptr ck)
        raises (::Components::InvalidConnection);

    CIAO::Active_Objref_Map ciao_publishes_[publish name]_map_;
#end foreach [publish name] with [eventtype]
    // Other CCMContext specific operations seem quite straightforward
    // to me.  Well, so far.
  };

  //////////////////////////////////////////////////////////////////
  // Component Servant Glue code implementation
  class [SERVANT]_Export [component name]_Servant
    : public virtual POA_[component name], // full skeleton name here
      public virtual PortableServer::RefCountServantBase
  {
  public:
    // Ctor.
    [component name]_Servant (CCM_[component name]_ptr executor);

    // Dtor.
    ~[component name]_Servant (void);

#foreach [operation] in all supported interfaces of own component and all inherited components

    // Generate the [operation] here.

#end

    // Operations for provides interfaces.
#foreach [facet name] with [facet type] in (list of all provided interfaces) generate:
    [facet type]_ptr provide_[facet name] ();
#end foreach [facet name] with [facet type]

    // Operations for receptacles interfaces.

#foreach [receptacle name] with [uses type] in (list of all 'uses' interfaces) generate:
# if [receptacle name] is a simplex receptacle ('uses')
    // Simplex [receptacle name] connection management operations
    void connect_[receptacle name] (in [uses type] c)
      raises (::Components::AlreadyConnected,
              ::Components::InvalidConnection);
    [uses type] disconnect_[receptacle name] ()
      raises (::Components::NoConnection);
    [uses type] get_connection_[receptacle name] ();
# else ([receptacle name] is a multiplex ('uses multiple') receptacle)
    // Multiplex [receptacle name] connection management operations
    ::Components::Cookie_ptr connect_[receptacle name] (in [uses type] c)
      raises (::Components::ExceedConnectionLimit,
              ::Components::InvalidConnection);
    [uses type] disconnect_[receptacle name] (in ::Components::Cookie_ptr ck)
      raises (::Components::InvalidConnection);
    [receptacle name]Connections get_connections_[receptacle name] ();
# endif [receptacle name]
#end foreach [receptacle name] with [uses type]

    // Operations for consumers interfaces.
#foreach [consumer name] with [eventtype] in (list of all consumers) generate:
    [eventtype]Consumer_ptr get_consumer_[consumer name] ();
#end foreach [facet name] with [eventtype]

    // Operations for emits interfaces.
#foreach [emit name] with [eventtype] in (list of all emitters) generate:
    void connect_[emit name] (in [eventtype]Consumer_ptr c)
      raises (::Components::AlreadyConnected);

    [eventtype]Consumer_ptr disconnect_[emit name] ()
      raises (::Components::NoConnection);
#end foreach [emit name] with [eventtype]

    // Operations for publishes interfaces.
#foreach [publish name] with [eventtype] in (list of all publishers) generate:
      ::Components::Cookie_ptr
      subscribe_[publish name] ([eventtype]Consumer_ptr c)
        raises (::Components::ExceededConnectionLimit);

      [eventtype]Consumer_ptr
      unsubscribe_[publish name] (::Components::Cookie_ptr ck)
        raises (::Components::InvalidConnection);
#end foreach [publish name] with [eventtype]

    // Operations for Navigation interface
    virtual CORBA::Object_ptr provide_facet (const char * name
                                             ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException ,
                       Components::InvalidName)) ;
    virtual ::Components::FacetDescriptions * get_all_facets (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::Components::FacetDescriptions * get_named_facets (const Components::NameList & names
                                                                ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException ,
                       Components::InvalidName));
    virtual CORBA::Boolean same_component (CORBA::Object_ptr object_ref
                                           ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));

    // Operations for Receptacles interface
    virtual ::Components::Cookie_ptr connect (const char * name,
                                            CORBA::Object_ptr connection
                                            ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName,
                       Components::InvalidConnection,
                       Components::AlreadyConnected,
                       Components::ExceededConnectionLimit));
    virtual void disconnect (const char * name,
                             Components::Cookie_ptr ck
                             ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName,
                       Components::InvalidConnection,
                       Components::CookieRequired,
                       Components::NoConnection));
    virtual ::Components::ConnectionDescriptions * get_connections (const char * name
                                                                    ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName));

    virtual ::Components::ReceptacleDescriptions * get_all_receptacles (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::Components::ReceptacleDescriptions * get_named_receptacles (const Components::NameList & names
                                                                          ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName));

    // Operations for Events interface
    virtual ::Components::EventConsumerBase_ptr get_consumer (const char * sink_name
                                                              ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName));
    virtual ::Components::Cookie_ptr subscribe (const char * publisher_name,
                                                Components::EventConsumerBase_ptr subscriber
                                                ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName,
                       Components::AlreadyConnected,
                       Components::InvalidConnection));
    virtual void unsubscribe (const char * publisher_name,
                              Components::Cookie_ptr ck
                              ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName,
                       Components::InvalidConnection));
    virtual void connect_consumer (const char * emitter_name,
                                   Components::EventConsumerBase_ptr consumer
                                   ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName,
                       Components::AlreadyConnected,
                       Components::InvalidConnection));
    virtual ::Components::EventConsumerBase_ptr disconnect_consumer (const char * source_name
                                                                     ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName,
                       Components::NoConnection));
    virtual ::Components::ConsumerDescriptions * get_all_consumers (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::Components::ConsumerDescriptions * get_named_consumers (const Components::NameList & names
                                                                      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName));
    virtual ::Components::EmitterDescriptions * get_all_emitters (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::Components::EmitterDescriptions * get_named_emitters (const Components::NameList & names
                                                                    ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName));
    virtual ::Components::PublisherDescriptions * get_all_publishers (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::Components::PublisherDescriptions * get_named_publishers (const Components::NameList & names
                                                                        ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidName));

    // Operations for CCMObject interface
    virtual ::CORBA::IRObject_ptr get_component_def (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::Components::CCMHome_ptr get_ccm_home (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::Components::PrimaryKeyBase * get_primary_key (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::NoKeyAvailable));
    virtual void configuration_complete (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::InvalidConfiguration));
    virtual void remove (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::RemoveFailure));
    virtual ::Components::ComponentPortDescription * get_all_ports (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));

  protected:
    // My Executor.
    CCM_[component name]_var executor_;

    // My Run-time Context.
    CCM_[component name]_Context_var context_;

    // Cached provided interfaces.
#foreach [facet name] with [facet type] in (list of all provided interfaces) generate:
    [facet type]_var provide_[facet name]_;
#end foreach [facet name] with [facet type]

#foreach [consumer name] with [eventtype] in (list of all consumers) generate:
    [eventtype]Consumer_var consumes_[consumer name]_;
#end foreach [consumer name] with [eventtype]

};


  //////////////////////////////////////////////////////////////////
  // Component Home Glue code implementation

  // Foreach component home
  class [SERVANT]_Export [home name]_Servant :
    public virtual POA_[home name], // full skeleton name here
    public virtual PortableServer::RefCountServantBase
  {
  public:
    // Ctor.
    [home anem]_Servant (CCM_[home name]_ptr exe,
                       CIAO::Session_Container *c);

    // Dtor.
    ~[home name]_Servant (void);

    // User defined and inherited operations
    // (Factories, Finders, and explicit operations.)

    // Operations for KeylessHome interface
    virtual ::Components::CCMObject_ptr create_component (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::CreateFailure));

    // Operations for Implicit Home interface
    virtual [component name]_ptr create (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::CreateFailure));

    // Operations for CCMHome interface
    virtual ::CORBA::IRObject_ptr get_component_def (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual ::CORBA::IRObject_ptr get_home_def (ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException));
    virtual void remove_component (Components::CCMObject_ptr comp
                                   ACE_ENV_ARG_DECL_WITH_DEFAULTS)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       Components::RemoveFailure));

  protected:
    // My Executor.
    CCM_[home name]_var executor_;

    // My Container
    CIAO::Session_Container *container_;
  };

  extern "C" [SERVANT]_Export ::PortableServer::Servant
  create[home name]_Servant (::Components::HomeExecutorBase_ptr p,
                             CIAO::Session_Container *c
                             ACE_ENV_ARG_DECL_WITH_DEFAULTS);
#if there are module definitions, preserve them all
}
#endif

#if defined (__ACE_INLINE__)
# include "[idl-basename]GS.inl"
#endif /* __ACE_INLINE__ */


#include "ace/post.h"
#endif /* CIAO_GLUE_SESSION_[idl-basename]GS_H */
