/*******************************************************************
 * Created Mon Jan 15 15:55:07 2001 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Client Stubs include file: (ir_c.h)
 * --------------------------------------------
 *
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    IRObject
 *    Contained
 *    Container
 *    IDLType
 *    Repository
 *    ModuleDef
 *    ConstantDef
 *    TypedefDef
 *    StructDef
 *    UnionDef
 *    EnumDef
 *    AliasDef
 *    PrimitiveDef
 *    StringDef
 *    SequenceDef
 *    ArrayDef
 *    ExceptionDef
 *    AttributeDef
 *    OperationDef
 *    InterfaceDef
 *
 */

#ifndef _ir_opr_c_HXX
#define _ir_opr_c_HXX

void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::DefinitionKind obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::DefinitionKind &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::IRObject_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::IRObject_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::Contained_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::Contained_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::Contained::Description &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::Contained::Description *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::Contained::Description *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::InterfaceDefSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::InterfaceDefSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::InterfaceDefSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ValueDefSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ValueDefSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ValueDefSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::AbstractInterfaceDefSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::AbstractInterfaceDefSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::AbstractInterfaceDefSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::LocalInterfaceDefSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::LocalInterfaceDefSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::LocalInterfaceDefSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ContainedSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ContainedSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ContainedSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::StructMember &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::StructMember *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::StructMember *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::StructMemberSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::StructMemberSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::StructMemberSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::Initializer &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::Initializer *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::Initializer *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::InitializerSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::InitializerSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::InitializerSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::UnionMember &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::UnionMember *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::UnionMember *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::UnionMemberSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::UnionMemberSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::UnionMemberSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::EnumMemberSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::EnumMemberSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::EnumMemberSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::Container_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::Container_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::Container::Description &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::Container::Description *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::Container::Description *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::Container::DescriptionSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::Container::DescriptionSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::Container::DescriptionSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::IDLType_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::IDLType_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::PrimitiveKind obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::PrimitiveKind &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::Repository_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::Repository_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ModuleDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ModuleDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ModuleDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ModuleDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ModuleDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ConstantDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ConstantDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ConstantDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ConstantDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ConstantDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::TypedefDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::TypedefDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::TypeDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::TypeDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::TypeDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::StructDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::StructDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::UnionDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::UnionDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::EnumDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::EnumDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::AliasDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::AliasDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::NativeDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::NativeDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::PrimitiveDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::PrimitiveDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::StringDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::StringDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::WstringDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::WstringDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::FixedDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::FixedDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::SequenceDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::SequenceDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ArrayDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ArrayDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ExceptionDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ExceptionDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ExceptionDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ExceptionDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ExceptionDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::AttributeMode obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::AttributeMode &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::AttributeDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::AttributeDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::AttributeDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::AttributeDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::AttributeDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::OperationMode obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::OperationMode &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ParameterMode obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ParameterMode &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ParameterDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ParameterDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ParameterDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ParDescriptionSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ParDescriptionSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ParDescriptionSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ContextIdSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ContextIdSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ContextIdSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ExceptionDefSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ExceptionDefSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ExceptionDefSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ExcDescriptionSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ExcDescriptionSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ExcDescriptionSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::OperationDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::OperationDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::OperationDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::OperationDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::OperationDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::RepositoryIdSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::RepositoryIdSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::RepositoryIdSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::OpDescriptionSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::OpDescriptionSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::OpDescriptionSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::AttrDescriptionSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::AttrDescriptionSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::AttrDescriptionSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::InterfaceDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::InterfaceDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::InterfaceDef::FullInterfaceDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::InterfaceDef::FullInterfaceDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::InterfaceDef::FullInterfaceDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::InterfaceDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::InterfaceDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::InterfaceDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ValueMember &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ValueMember *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ValueMember *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ValueMemberSeq &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ValueMemberSeq *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ValueMemberSeq *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ValueMemberDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ValueMemberDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ValueDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ValueDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ValueDef::FullValueDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ValueDef::FullValueDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ValueDef::FullValueDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ValueDescription &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ValueDescription *obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ValueDescription *&obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ValueBoxDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ValueBoxDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::AbstractInterfaceDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::AbstractInterfaceDef_ptr &obj);
void OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::LocalInterfaceDef_ptr obj);
CORBA::Boolean OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::LocalInterfaceDef_ptr &obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::DefinitionKind &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::DefinitionKind &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::IRObject_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::IRObject_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::IRObject_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::Contained_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::Contained_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::Contained_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::Contained::Description &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::Contained::Description &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::InterfaceDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::InterfaceDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ValueDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ValueDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::AbstractInterfaceDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::AbstractInterfaceDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::LocalInterfaceDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::LocalInterfaceDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ContainedSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ContainedSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::StructMember &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::StructMember &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::StructMemberSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::StructMemberSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::Initializer &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::Initializer &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::InitializerSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::InitializerSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::UnionMember &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::UnionMember &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::UnionMemberSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::UnionMemberSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::EnumMemberSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::EnumMemberSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::Container_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::Container_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::Container_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::Container::Description &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::Container::Description &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::Container::DescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::Container::DescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::IDLType_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::IDLType_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::IDLType_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::PrimitiveKind &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::PrimitiveKind &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::Repository_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::Repository_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::Repository_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::ModuleDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ModuleDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ModuleDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ModuleDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ModuleDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::ConstantDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ConstantDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ConstantDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ConstantDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ConstantDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::TypedefDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::TypedefDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::TypedefDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::TypeDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::TypeDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::StructDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::StructDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::StructDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::UnionDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::UnionDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::UnionDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::EnumDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::EnumDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::EnumDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::AliasDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::AliasDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::AliasDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::NativeDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::NativeDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::NativeDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::PrimitiveDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::PrimitiveDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::PrimitiveDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::StringDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::StringDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::StringDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::WstringDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::WstringDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::WstringDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::FixedDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::FixedDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::FixedDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::SequenceDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::SequenceDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::SequenceDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::ArrayDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ArrayDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ArrayDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::ExceptionDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ExceptionDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ExceptionDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ExceptionDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ExceptionDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::AttributeMode &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::AttributeMode &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::AttributeDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::AttributeDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::AttributeDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::AttributeDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::AttributeDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::OperationMode &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::OperationMode &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ParameterMode &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ParameterMode &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ParameterDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ParameterDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ParDescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ParDescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ContextIdSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ContextIdSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ExceptionDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ExceptionDefSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ExcDescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ExcDescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::OperationDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::OperationDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::OperationDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::OperationDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::OperationDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::RepositoryIdSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::RepositoryIdSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::OpDescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::OpDescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::AttrDescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::AttrDescriptionSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::InterfaceDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::InterfaceDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::InterfaceDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::InterfaceDef::FullInterfaceDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::InterfaceDef::FullInterfaceDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::InterfaceDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::InterfaceDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ValueMember &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ValueMember &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ValueMemberSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ValueMemberSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::ValueMemberDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ValueMemberDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ValueMemberDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::ValueDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ValueDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ValueDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ValueDef::FullValueDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ValueDef::FullValueDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ValueDescription &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ValueDescription &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::ValueBoxDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ValueBoxDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::ValueBoxDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::AbstractInterfaceDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::AbstractInterfaceDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::AbstractInterfaceDef_var &_obj);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &mb, CORBA::LocalInterfaceDef_ptr _obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::LocalInterfaceDef_ptr &_obj);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &mb, CORBA::LocalInterfaceDef_var &_obj);


#endif
