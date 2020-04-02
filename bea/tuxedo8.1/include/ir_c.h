/*******************************************************************
 * Created Mon Jan 29 09:35:23 2001 by Tuxedo V8.0-01 (C++ Bindings)
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
 *    NativeDef
 *    PrimitiveDef
 *    StringDef
 *    WstringDef
 *    FixedDef
 *    SequenceDef
 *    ArrayDef
 *    ExceptionDef
 *    AttributeDef
 *    OperationDef
 *    InterfaceDef
 *    ValueMemberDef
 *    ValueDef
 *    ValueBoxDef
 *    AbstractInterfaceDef
 *    LocalInterfaceDef
 *
 */


#ifndef _ir_c_H
#define _ir_c_H

    public:
        class	IRObject;
        typedef	IRObject *	IRObject_ptr;
        class IRObject_out;

        class OBBEXPDLL IRObject_var : public _var {
            public:
                IRObject_var();
                inline IRObject_var(IRObject_ptr p) {ptr_ = p; }
                IRObject_var(const IRObject_var &a);
                ~IRObject_var()
                    { free();}

                IRObject_var &operator=(IRObject_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                IRObject_var &operator=(const IRObject_var &a);
                inline IRObject_ptr in () const { return ptr_; }
                inline IRObject_ptr & inout () { return ptr_; }
                IRObject_ptr & out ();
                IRObject_ptr _retn ();

                inline operator IRObject_ptr&() { return ptr_; }
                inline operator const IRObject_ptr&() const { return ptr_; }
                inline IRObject_ptr operator->() const { return ptr_; }

                inline IRObject_ptr & ptr () { return ptr_; }
            protected:
                IRObject_ptr ptr_;
                void free();
                void reset(IRObject_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class IRObject_var


        class	Contained;
        typedef	Contained *	Contained_ptr;
        class Contained_out;

        class OBBEXPDLL Contained_var : public _var {
            public:
                Contained_var();
                inline Contained_var(Contained_ptr p) {ptr_ = p; }
                Contained_var(const Contained_var &a);
                ~Contained_var()
                    { free();}

                Contained_var &operator=(Contained_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Contained_var &operator=(const Contained_var &a);
                inline Contained_ptr in () const { return ptr_; }
                inline Contained_ptr & inout () { return ptr_; }
                Contained_ptr & out ();
                Contained_ptr _retn ();

                inline operator Contained_ptr&() { return ptr_; }
                inline operator const Contained_ptr&() const { return ptr_; }
                inline Contained_ptr operator->() const { return ptr_; }

                inline Contained_ptr & ptr () { return ptr_; }
            protected:
                Contained_ptr ptr_;
                void free();
                void reset(Contained_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class Contained_var


        class	Container;
        typedef	Container *	Container_ptr;
        class Container_out;

        class OBBEXPDLL Container_var : public _var {
            public:
                Container_var();
                inline Container_var(Container_ptr p) {ptr_ = p; }
                Container_var(const Container_var &a);
                ~Container_var()
                    { free();}

                Container_var &operator=(Container_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Container_var &operator=(const Container_var &a);
                inline Container_ptr in () const { return ptr_; }
                inline Container_ptr & inout () { return ptr_; }
                Container_ptr & out ();
                Container_ptr _retn ();

                inline operator Container_ptr&() { return ptr_; }
                inline operator const Container_ptr&() const { return ptr_; }
                inline Container_ptr operator->() const { return ptr_; }

                inline Container_ptr & ptr () { return ptr_; }
            protected:
                Container_ptr ptr_;
                void free();
                void reset(Container_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class Container_var


        class	IDLType;
        typedef	IDLType *	IDLType_ptr;
        class IDLType_out;

        class OBBEXPDLL IDLType_var : public _var {
            public:
                IDLType_var();
                inline IDLType_var(IDLType_ptr p) {ptr_ = p; }
                IDLType_var(const IDLType_var &a);
                ~IDLType_var()
                    { free();}

                IDLType_var &operator=(IDLType_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                IDLType_var &operator=(const IDLType_var &a);
                inline IDLType_ptr in () const { return ptr_; }
                inline IDLType_ptr & inout () { return ptr_; }
                IDLType_ptr & out ();
                IDLType_ptr _retn ();

                inline operator IDLType_ptr&() { return ptr_; }
                inline operator const IDLType_ptr&() const { return ptr_; }
                inline IDLType_ptr operator->() const { return ptr_; }

                inline IDLType_ptr & ptr () { return ptr_; }
            protected:
                IDLType_ptr ptr_;
                void free();
                void reset(IDLType_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class IDLType_var


        class	Repository;
        typedef	Repository *	Repository_ptr;
        class Repository_out;

        class OBBEXPDLL Repository_var : public _var {
            public:
                Repository_var();
                inline Repository_var(Repository_ptr p) {ptr_ = p; }
                Repository_var(const Repository_var &a);
                ~Repository_var()
                    { free();}

                Repository_var &operator=(Repository_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Repository_var &operator=(const Repository_var &a);
                inline Repository_ptr in () const { return ptr_; }
                inline Repository_ptr & inout () { return ptr_; }
                Repository_ptr & out ();
                Repository_ptr _retn ();

                inline operator Repository_ptr&() { return ptr_; }
                inline operator const Repository_ptr&() const { return ptr_; }
                inline Repository_ptr operator->() const { return ptr_; }

                inline Repository_ptr & ptr () { return ptr_; }
            protected:
                Repository_ptr ptr_;
                void free();
                void reset(Repository_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class Repository_var


        class	ModuleDef;
        typedef	ModuleDef *	ModuleDef_ptr;
        class ModuleDef_out;

        class OBBEXPDLL ModuleDef_var : public _var {
            public:
                ModuleDef_var();
                inline ModuleDef_var(ModuleDef_ptr p) {ptr_ = p; }
                ModuleDef_var(const ModuleDef_var &a);
                ~ModuleDef_var()
                    { free();}

                ModuleDef_var &operator=(ModuleDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                ModuleDef_var &operator=(const ModuleDef_var &a);
                inline ModuleDef_ptr in () const { return ptr_; }
                inline ModuleDef_ptr & inout () { return ptr_; }
                ModuleDef_ptr & out ();
                ModuleDef_ptr _retn ();

                inline operator ModuleDef_ptr&() { return ptr_; }
                inline operator const ModuleDef_ptr&() const { return ptr_; }
                inline ModuleDef_ptr operator->() const { return ptr_; }

                inline ModuleDef_ptr & ptr () { return ptr_; }
            protected:
                ModuleDef_ptr ptr_;
                void free();
                void reset(ModuleDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class ModuleDef_var


        class	ConstantDef;
        typedef	ConstantDef *	ConstantDef_ptr;
        class ConstantDef_out;

        class OBBEXPDLL ConstantDef_var : public _var {
            public:
                ConstantDef_var();
                inline ConstantDef_var(ConstantDef_ptr p) {ptr_ = p; }
                ConstantDef_var(const ConstantDef_var &a);
                ~ConstantDef_var()
                    { free();}

                ConstantDef_var &operator=(ConstantDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                ConstantDef_var &operator=(const ConstantDef_var &a);
                inline ConstantDef_ptr in () const { return ptr_; }
                inline ConstantDef_ptr & inout () { return ptr_; }
                ConstantDef_ptr & out ();
                ConstantDef_ptr _retn ();

                inline operator ConstantDef_ptr&() { return ptr_; }
                inline operator const ConstantDef_ptr&() const { return ptr_; }
                inline ConstantDef_ptr operator->() const { return ptr_; }

                inline ConstantDef_ptr & ptr () { return ptr_; }
            protected:
                ConstantDef_ptr ptr_;
                void free();
                void reset(ConstantDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class ConstantDef_var


        class	TypedefDef;
        typedef	TypedefDef *	TypedefDef_ptr;
        class TypedefDef_out;

        class OBBEXPDLL TypedefDef_var : public _var {
            public:
                TypedefDef_var();
                inline TypedefDef_var(TypedefDef_ptr p) {ptr_ = p; }
                TypedefDef_var(const TypedefDef_var &a);
                ~TypedefDef_var()
                    { free();}

                TypedefDef_var &operator=(TypedefDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                TypedefDef_var &operator=(const TypedefDef_var &a);
                inline TypedefDef_ptr in () const { return ptr_; }
                inline TypedefDef_ptr & inout () { return ptr_; }
                TypedefDef_ptr & out ();
                TypedefDef_ptr _retn ();

                inline operator TypedefDef_ptr&() { return ptr_; }
                inline operator const TypedefDef_ptr&() const { return ptr_; }
                inline TypedefDef_ptr operator->() const { return ptr_; }

                inline TypedefDef_ptr & ptr () { return ptr_; }
            protected:
                TypedefDef_ptr ptr_;
                void free();
                void reset(TypedefDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class TypedefDef_var


        class	StructDef;
        typedef	StructDef *	StructDef_ptr;
        class StructDef_out;

        class OBBEXPDLL StructDef_var : public _var {
            public:
                StructDef_var();
                inline StructDef_var(StructDef_ptr p) {ptr_ = p; }
                StructDef_var(const StructDef_var &a);
                ~StructDef_var()
                    { free();}

                StructDef_var &operator=(StructDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                StructDef_var &operator=(const StructDef_var &a);
                inline StructDef_ptr in () const { return ptr_; }
                inline StructDef_ptr & inout () { return ptr_; }
                StructDef_ptr & out ();
                StructDef_ptr _retn ();

                inline operator StructDef_ptr&() { return ptr_; }
                inline operator const StructDef_ptr&() const { return ptr_; }
                inline StructDef_ptr operator->() const { return ptr_; }

                inline StructDef_ptr & ptr () { return ptr_; }
            protected:
                StructDef_ptr ptr_;
                void free();
                void reset(StructDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class StructDef_var


        class	UnionDef;
        typedef	UnionDef *	UnionDef_ptr;
        class UnionDef_out;

        class OBBEXPDLL UnionDef_var : public _var {
            public:
                UnionDef_var();
                inline UnionDef_var(UnionDef_ptr p) {ptr_ = p; }
                UnionDef_var(const UnionDef_var &a);
                ~UnionDef_var()
                    { free();}

                UnionDef_var &operator=(UnionDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                UnionDef_var &operator=(const UnionDef_var &a);
                inline UnionDef_ptr in () const { return ptr_; }
                inline UnionDef_ptr & inout () { return ptr_; }
                UnionDef_ptr & out ();
                UnionDef_ptr _retn ();

                inline operator UnionDef_ptr&() { return ptr_; }
                inline operator const UnionDef_ptr&() const { return ptr_; }
                inline UnionDef_ptr operator->() const { return ptr_; }

                inline UnionDef_ptr & ptr () { return ptr_; }
            protected:
                UnionDef_ptr ptr_;
                void free();
                void reset(UnionDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class UnionDef_var


        class	EnumDef;
        typedef	EnumDef *	EnumDef_ptr;
        class EnumDef_out;

        class OBBEXPDLL EnumDef_var : public _var {
            public:
                EnumDef_var();
                inline EnumDef_var(EnumDef_ptr p) {ptr_ = p; }
                EnumDef_var(const EnumDef_var &a);
                ~EnumDef_var()
                    { free();}

                EnumDef_var &operator=(EnumDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                EnumDef_var &operator=(const EnumDef_var &a);
                inline EnumDef_ptr in () const { return ptr_; }
                inline EnumDef_ptr & inout () { return ptr_; }
                EnumDef_ptr & out ();
                EnumDef_ptr _retn ();

                inline operator EnumDef_ptr&() { return ptr_; }
                inline operator const EnumDef_ptr&() const { return ptr_; }
                inline EnumDef_ptr operator->() const { return ptr_; }

                inline EnumDef_ptr & ptr () { return ptr_; }
            protected:
                EnumDef_ptr ptr_;
                void free();
                void reset(EnumDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class EnumDef_var


        class	AliasDef;
        typedef	AliasDef *	AliasDef_ptr;
        class AliasDef_out;

        class OBBEXPDLL AliasDef_var : public _var {
            public:
                AliasDef_var();
                inline AliasDef_var(AliasDef_ptr p) {ptr_ = p; }
                AliasDef_var(const AliasDef_var &a);
                ~AliasDef_var()
                    { free();}

                AliasDef_var &operator=(AliasDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                AliasDef_var &operator=(const AliasDef_var &a);
                inline AliasDef_ptr in () const { return ptr_; }
                inline AliasDef_ptr & inout () { return ptr_; }
                AliasDef_ptr & out ();
                AliasDef_ptr _retn ();

                inline operator AliasDef_ptr&() { return ptr_; }
                inline operator const AliasDef_ptr&() const { return ptr_; }
                inline AliasDef_ptr operator->() const { return ptr_; }

                inline AliasDef_ptr & ptr () { return ptr_; }
            protected:
                AliasDef_ptr ptr_;
                void free();
                void reset(AliasDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class AliasDef_var


        class	NativeDef;
        typedef	NativeDef *	NativeDef_ptr;
        class NativeDef_out;

        class OBBEXPDLL NativeDef_var : public _var {
            public:
                NativeDef_var();
                inline NativeDef_var(NativeDef_ptr p) {ptr_ = p; }
                NativeDef_var(const NativeDef_var &a);
                ~NativeDef_var()
                    { free();}

                NativeDef_var &operator=(NativeDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                NativeDef_var &operator=(const NativeDef_var &a);
                inline NativeDef_ptr in () const { return ptr_; }
                inline NativeDef_ptr & inout () { return ptr_; }
                NativeDef_ptr & out ();
                NativeDef_ptr _retn ();

                inline operator NativeDef_ptr&() { return ptr_; }
                inline operator const NativeDef_ptr&() const { return ptr_; }
                inline NativeDef_ptr operator->() const { return ptr_; }

                inline NativeDef_ptr & ptr () { return ptr_; }
            protected:
                NativeDef_ptr ptr_;
                void free();
                void reset(NativeDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class NativeDef_var


        class	PrimitiveDef;
        typedef	PrimitiveDef *	PrimitiveDef_ptr;
        class PrimitiveDef_out;

        class OBBEXPDLL PrimitiveDef_var : public _var {
            public:
                PrimitiveDef_var();
                inline PrimitiveDef_var(PrimitiveDef_ptr p) {ptr_ = p; }
                PrimitiveDef_var(const PrimitiveDef_var &a);
                ~PrimitiveDef_var()
                    { free();}

                PrimitiveDef_var &operator=(PrimitiveDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                PrimitiveDef_var &operator=(const PrimitiveDef_var &a);
                inline PrimitiveDef_ptr in () const { return ptr_; }
                inline PrimitiveDef_ptr & inout () { return ptr_; }
                PrimitiveDef_ptr & out ();
                PrimitiveDef_ptr _retn ();

                inline operator PrimitiveDef_ptr&() { return ptr_; }
                inline operator const PrimitiveDef_ptr&() const { return ptr_; }
                inline PrimitiveDef_ptr operator->() const { return ptr_; }

                inline PrimitiveDef_ptr & ptr () { return ptr_; }
            protected:
                PrimitiveDef_ptr ptr_;
                void free();
                void reset(PrimitiveDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class PrimitiveDef_var


        class	StringDef;
        typedef	StringDef *	StringDef_ptr;
        class StringDef_out;

        class OBBEXPDLL StringDef_var : public _var {
            public:
                StringDef_var();
                inline StringDef_var(StringDef_ptr p) {ptr_ = p; }
                StringDef_var(const StringDef_var &a);
                ~StringDef_var()
                    { free();}

                StringDef_var &operator=(StringDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                StringDef_var &operator=(const StringDef_var &a);
                inline StringDef_ptr in () const { return ptr_; }
                inline StringDef_ptr & inout () { return ptr_; }
                StringDef_ptr & out ();
                StringDef_ptr _retn ();

                inline operator StringDef_ptr&() { return ptr_; }
                inline operator const StringDef_ptr&() const { return ptr_; }
                inline StringDef_ptr operator->() const { return ptr_; }

                inline StringDef_ptr & ptr () { return ptr_; }
            protected:
                StringDef_ptr ptr_;
                void free();
                void reset(StringDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class StringDef_var


        class	WstringDef;
        typedef	WstringDef *	WstringDef_ptr;
        class WstringDef_out;

        class OBBEXPDLL WstringDef_var : public _var {
            public:
                WstringDef_var();
                inline WstringDef_var(WstringDef_ptr p) {ptr_ = p; }
                WstringDef_var(const WstringDef_var &a);
                ~WstringDef_var()
                    { free();}

                WstringDef_var &operator=(WstringDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                WstringDef_var &operator=(const WstringDef_var &a);
                inline WstringDef_ptr in () const { return ptr_; }
                inline WstringDef_ptr & inout () { return ptr_; }
                WstringDef_ptr & out ();
                WstringDef_ptr _retn ();

                inline operator WstringDef_ptr&() { return ptr_; }
                inline operator const WstringDef_ptr&() const { return ptr_; }
                inline WstringDef_ptr operator->() const { return ptr_; }

                inline WstringDef_ptr & ptr () { return ptr_; }
            protected:
                WstringDef_ptr ptr_;
                void free();
                void reset(WstringDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class WstringDef_var


        class	FixedDef;
        typedef	FixedDef *	FixedDef_ptr;
        class FixedDef_out;

        class OBBEXPDLL FixedDef_var : public _var {
            public:
                FixedDef_var();
                inline FixedDef_var(FixedDef_ptr p) {ptr_ = p; }
                FixedDef_var(const FixedDef_var &a);
                ~FixedDef_var()
                    { free();}

                FixedDef_var &operator=(FixedDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                FixedDef_var &operator=(const FixedDef_var &a);
                inline FixedDef_ptr in () const { return ptr_; }
                inline FixedDef_ptr & inout () { return ptr_; }
                FixedDef_ptr & out ();
                FixedDef_ptr _retn ();

                inline operator FixedDef_ptr&() { return ptr_; }
                inline operator const FixedDef_ptr&() const { return ptr_; }
                inline FixedDef_ptr operator->() const { return ptr_; }

                inline FixedDef_ptr & ptr () { return ptr_; }
            protected:
                FixedDef_ptr ptr_;
                void free();
                void reset(FixedDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class FixedDef_var


        class	SequenceDef;
        typedef	SequenceDef *	SequenceDef_ptr;
        class SequenceDef_out;

        class OBBEXPDLL SequenceDef_var : public _var {
            public:
                SequenceDef_var();
                inline SequenceDef_var(SequenceDef_ptr p) {ptr_ = p; }
                SequenceDef_var(const SequenceDef_var &a);
                ~SequenceDef_var()
                    { free();}

                SequenceDef_var &operator=(SequenceDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                SequenceDef_var &operator=(const SequenceDef_var &a);
                inline SequenceDef_ptr in () const { return ptr_; }
                inline SequenceDef_ptr & inout () { return ptr_; }
                SequenceDef_ptr & out ();
                SequenceDef_ptr _retn ();

                inline operator SequenceDef_ptr&() { return ptr_; }
                inline operator const SequenceDef_ptr&() const { return ptr_; }
                inline SequenceDef_ptr operator->() const { return ptr_; }

                inline SequenceDef_ptr & ptr () { return ptr_; }
            protected:
                SequenceDef_ptr ptr_;
                void free();
                void reset(SequenceDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class SequenceDef_var


        class	ArrayDef;
        typedef	ArrayDef *	ArrayDef_ptr;
        class ArrayDef_out;

        class OBBEXPDLL ArrayDef_var : public _var {
            public:
                ArrayDef_var();
                inline ArrayDef_var(ArrayDef_ptr p) {ptr_ = p; }
                ArrayDef_var(const ArrayDef_var &a);
                ~ArrayDef_var()
                    { free();}

                ArrayDef_var &operator=(ArrayDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                ArrayDef_var &operator=(const ArrayDef_var &a);
                inline ArrayDef_ptr in () const { return ptr_; }
                inline ArrayDef_ptr & inout () { return ptr_; }
                ArrayDef_ptr & out ();
                ArrayDef_ptr _retn ();

                inline operator ArrayDef_ptr&() { return ptr_; }
                inline operator const ArrayDef_ptr&() const { return ptr_; }
                inline ArrayDef_ptr operator->() const { return ptr_; }

                inline ArrayDef_ptr & ptr () { return ptr_; }
            protected:
                ArrayDef_ptr ptr_;
                void free();
                void reset(ArrayDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class ArrayDef_var


        class	ExceptionDef;
        typedef	ExceptionDef *	ExceptionDef_ptr;
        class ExceptionDef_out;

        class OBBEXPDLL ExceptionDef_var : public _var {
            public:
                ExceptionDef_var();
                inline ExceptionDef_var(ExceptionDef_ptr p) {ptr_ = p; }
                ExceptionDef_var(const ExceptionDef_var &a);
                ~ExceptionDef_var()
                    { free();}

                ExceptionDef_var &operator=(ExceptionDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                ExceptionDef_var &operator=(const ExceptionDef_var &a);
                inline ExceptionDef_ptr in () const { return ptr_; }
                inline ExceptionDef_ptr & inout () { return ptr_; }
                ExceptionDef_ptr & out ();
                ExceptionDef_ptr _retn ();

                inline operator ExceptionDef_ptr&() { return ptr_; }
                inline operator const ExceptionDef_ptr&() const { return ptr_; }
                inline ExceptionDef_ptr operator->() const { return ptr_; }

                inline ExceptionDef_ptr & ptr () { return ptr_; }
            protected:
                ExceptionDef_ptr ptr_;
                void free();
                void reset(ExceptionDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class ExceptionDef_var


        class	AttributeDef;
        typedef	AttributeDef *	AttributeDef_ptr;
        class AttributeDef_out;

        class OBBEXPDLL AttributeDef_var : public _var {
            public:
                AttributeDef_var();
                inline AttributeDef_var(AttributeDef_ptr p) {ptr_ = p; }
                AttributeDef_var(const AttributeDef_var &a);
                ~AttributeDef_var()
                    { free();}

                AttributeDef_var &operator=(AttributeDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                AttributeDef_var &operator=(const AttributeDef_var &a);
                inline AttributeDef_ptr in () const { return ptr_; }
                inline AttributeDef_ptr & inout () { return ptr_; }
                AttributeDef_ptr & out ();
                AttributeDef_ptr _retn ();

                inline operator AttributeDef_ptr&() { return ptr_; }
                inline operator const AttributeDef_ptr&() const { return ptr_; }
                inline AttributeDef_ptr operator->() const { return ptr_; }

                inline AttributeDef_ptr & ptr () { return ptr_; }
            protected:
                AttributeDef_ptr ptr_;
                void free();
                void reset(AttributeDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class AttributeDef_var


        class OperationDef_out;

        class OBBEXPDLL OperationDef_var : public _var {
            public:
                OperationDef_var();
                inline OperationDef_var(OperationDef_ptr p) {ptr_ = p; }
                OperationDef_var(const OperationDef_var &a);
                ~OperationDef_var()
                    { free();}

                OperationDef_var &operator=(OperationDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                OperationDef_var &operator=(const OperationDef_var &a);
                inline OperationDef_ptr in () const { return ptr_; }
                inline OperationDef_ptr & inout () { return ptr_; }
                OperationDef_ptr & out ();
                OperationDef_ptr _retn ();

                inline operator OperationDef_ptr&() { return ptr_; }
                inline operator const OperationDef_ptr&() const { return ptr_; }
                inline OperationDef_ptr operator->() const { return ptr_; }

                inline OperationDef_ptr & ptr () { return ptr_; }
            protected:
                OperationDef_ptr ptr_;
                void free();
                void reset(OperationDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class OperationDef_var


        class InterfaceDef_out;

        class OBBEXPDLL InterfaceDef_var : public _var {
            public:
                InterfaceDef_var();
                inline InterfaceDef_var(InterfaceDef_ptr p) {ptr_ = p; }
                InterfaceDef_var(const InterfaceDef_var &a);
                ~InterfaceDef_var()
                    { free();}

                InterfaceDef_var &operator=(InterfaceDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                InterfaceDef_var &operator=(const InterfaceDef_var &a);
                inline InterfaceDef_ptr in () const { return ptr_; }
                inline InterfaceDef_ptr & inout () { return ptr_; }
                InterfaceDef_ptr & out ();
                InterfaceDef_ptr _retn ();

                inline operator InterfaceDef_ptr&() { return ptr_; }
                inline operator const InterfaceDef_ptr&() const { return ptr_; }
                inline InterfaceDef_ptr operator->() const { return ptr_; }

                inline InterfaceDef_ptr & ptr () { return ptr_; }
            protected:
                InterfaceDef_ptr ptr_;
                void free();
                void reset(InterfaceDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class InterfaceDef_var


        class	ValueMemberDef;
        typedef	ValueMemberDef *	ValueMemberDef_ptr;
        class ValueMemberDef_out;

        class OBBEXPDLL ValueMemberDef_var : public _var {
            public:
                ValueMemberDef_var();
                inline ValueMemberDef_var(ValueMemberDef_ptr p) {ptr_ = p; }
                ValueMemberDef_var(const ValueMemberDef_var &a);
                ~ValueMemberDef_var()
                    { free();}

                ValueMemberDef_var &operator=(ValueMemberDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                ValueMemberDef_var &operator=(const ValueMemberDef_var &a);
                inline ValueMemberDef_ptr in () const { return ptr_; }
                inline ValueMemberDef_ptr & inout () { return ptr_; }
                ValueMemberDef_ptr & out ();
                ValueMemberDef_ptr _retn ();

                inline operator ValueMemberDef_ptr&() { return ptr_; }
                inline operator const ValueMemberDef_ptr&() const { return ptr_; }
                inline ValueMemberDef_ptr operator->() const { return ptr_; }

                inline ValueMemberDef_ptr & ptr () { return ptr_; }
            protected:
                ValueMemberDef_ptr ptr_;
                void free();
                void reset(ValueMemberDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class ValueMemberDef_var


        class	ValueDef;
        typedef	ValueDef *	ValueDef_ptr;
        class ValueDef_out;

        class OBBEXPDLL ValueDef_var : public _var {
            public:
                ValueDef_var();
                inline ValueDef_var(ValueDef_ptr p) {ptr_ = p; }
                ValueDef_var(const ValueDef_var &a);
                ~ValueDef_var()
                    { free();}

                ValueDef_var &operator=(ValueDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                ValueDef_var &operator=(const ValueDef_var &a);
                inline ValueDef_ptr in () const { return ptr_; }
                inline ValueDef_ptr & inout () { return ptr_; }
                ValueDef_ptr & out ();
                ValueDef_ptr _retn ();

                inline operator ValueDef_ptr&() { return ptr_; }
                inline operator const ValueDef_ptr&() const { return ptr_; }
                inline ValueDef_ptr operator->() const { return ptr_; }

                inline ValueDef_ptr & ptr () { return ptr_; }
            protected:
                ValueDef_ptr ptr_;
                void free();
                void reset(ValueDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class ValueDef_var


        class	ValueBoxDef;
        typedef	ValueBoxDef *	ValueBoxDef_ptr;
        class ValueBoxDef_out;

        class OBBEXPDLL ValueBoxDef_var : public _var {
            public:
                ValueBoxDef_var();
                inline ValueBoxDef_var(ValueBoxDef_ptr p) {ptr_ = p; }
                ValueBoxDef_var(const ValueBoxDef_var &a);
                ~ValueBoxDef_var()
                    { free();}

                ValueBoxDef_var &operator=(ValueBoxDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                ValueBoxDef_var &operator=(const ValueBoxDef_var &a);
                inline ValueBoxDef_ptr in () const { return ptr_; }
                inline ValueBoxDef_ptr & inout () { return ptr_; }
                ValueBoxDef_ptr & out ();
                ValueBoxDef_ptr _retn ();

                inline operator ValueBoxDef_ptr&() { return ptr_; }
                inline operator const ValueBoxDef_ptr&() const { return ptr_; }
                inline ValueBoxDef_ptr operator->() const { return ptr_; }

                inline ValueBoxDef_ptr & ptr () { return ptr_; }
            protected:
                ValueBoxDef_ptr ptr_;
                void free();
                void reset(ValueBoxDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class ValueBoxDef_var


        class	AbstractInterfaceDef;
        typedef	AbstractInterfaceDef *	AbstractInterfaceDef_ptr;
        class AbstractInterfaceDef_out;

        class OBBEXPDLL AbstractInterfaceDef_var : public _var {
            public:
                AbstractInterfaceDef_var();
                inline AbstractInterfaceDef_var(AbstractInterfaceDef_ptr p) {ptr_ = p; }
                AbstractInterfaceDef_var(const AbstractInterfaceDef_var &a);
                ~AbstractInterfaceDef_var()
                    { free();}

                AbstractInterfaceDef_var &operator=(AbstractInterfaceDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                AbstractInterfaceDef_var &operator=(const AbstractInterfaceDef_var &a);
                inline AbstractInterfaceDef_ptr in () const { return ptr_; }
                inline AbstractInterfaceDef_ptr & inout () { return ptr_; }
                AbstractInterfaceDef_ptr & out ();
                AbstractInterfaceDef_ptr _retn ();

                inline operator AbstractInterfaceDef_ptr&() { return ptr_; }
                inline operator const AbstractInterfaceDef_ptr&() const { return ptr_; }
                inline AbstractInterfaceDef_ptr operator->() const { return ptr_; }

                inline AbstractInterfaceDef_ptr & ptr () { return ptr_; }
            protected:
                AbstractInterfaceDef_ptr ptr_;
                void free();
                void reset(AbstractInterfaceDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class AbstractInterfaceDef_var


        class	LocalInterfaceDef;
        typedef	LocalInterfaceDef *	LocalInterfaceDef_ptr;
        class LocalInterfaceDef_out;

        class OBBEXPDLL LocalInterfaceDef_var : public _var {
            public:
                LocalInterfaceDef_var();
                inline LocalInterfaceDef_var(LocalInterfaceDef_ptr p) {ptr_ = p; }
                LocalInterfaceDef_var(const LocalInterfaceDef_var &a);
                ~LocalInterfaceDef_var()
                    { free();}

                LocalInterfaceDef_var &operator=(LocalInterfaceDef_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                LocalInterfaceDef_var &operator=(const LocalInterfaceDef_var &a);
                inline LocalInterfaceDef_ptr in () const { return ptr_; }
                inline LocalInterfaceDef_ptr & inout () { return ptr_; }
                LocalInterfaceDef_ptr & out ();
                LocalInterfaceDef_ptr _retn ();

                inline operator LocalInterfaceDef_ptr&() { return ptr_; }
                inline operator const LocalInterfaceDef_ptr&() const { return ptr_; }
                inline LocalInterfaceDef_ptr operator->() const { return ptr_; }

                inline LocalInterfaceDef_ptr & ptr () { return ptr_; }
            protected:
                LocalInterfaceDef_ptr ptr_;
                void free();
                void reset(LocalInterfaceDef_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const _var &);
        };  // class LocalInterfaceDef_var


        static const TypeCode_ptr _tc_Identifier;
        typedef String_out ScopedName_out;
        typedef String_var ScopedName_var;
        static const TypeCode_ptr _tc_ScopedName;
        static const TypeCode_ptr _tc_RepositoryId;


        enum DefinitionKind { dk_none, dk_all, dk_Attribute, dk_Constant, dk_Exception, dk_Interface, dk_Module, dk_Operation, dk_Typedef, dk_Alias, dk_Struct, dk_Union, dk_Enum, dk_Primitive, dk_String, dk_Sequence, dk_Array, dk_Repository, dk_Wstring, dk_Fixed, dk_Value, dk_ValueBox, dk_ValueMember, dk_Native, dk_AbstractInterface, dk_LocalInterface };
        typedef DefinitionKind & DefinitionKind_out ;
        static const TypeCode_ptr _tc_DefinitionKind;


        static const TypeCode_ptr _tc_IRObject;
        class OBBEXPDLL IRObject : public virtual Object
         {
            public:
                static IRObject_ptr _duplicate(IRObject_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static IRObject_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static IRObject_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual void destroy (); 

                virtual DefinitionKind def_kind (); 

            protected:
                IRObject(Object_ptr obj = 0);
                virtual ~IRObject(){ }

            private:
                IRObject( const IRObject&) { }
                void operator=(const IRObject&) { }
                ORB_ptr pORB;
        };  // class IRObject



        class OBBEXPDLL IRObject_out
         {
            public:
                IRObject_out (IRObject_ptr & p);
                IRObject_out (IRObject_var & p);
                IRObject_out (const IRObject_out & p) : ptr_(p.ptr_) {}
                IRObject_out & operator=(const IRObject_out & a) {
                    ptr_ = a.ptr_; return *this;}
                IRObject_out & operator=(const IRObject_var & a);
                IRObject_out & operator=(IRObject_ptr p) {
                ptr_ = p; return *this;}
                inline operator IRObject_ptr & () { return ptr_; }
                inline IRObject_ptr & ptr () { return ptr_; }
                inline IRObject_ptr operator->() { return ptr_; }
            private:
                IRObject_ptr & ptr_;
        };  // class IRObject_out

        typedef Char * VersionSpec;
        typedef String_out VersionSpec_out;
        typedef String_var VersionSpec_var;
        static const TypeCode_ptr _tc_VersionSpec;


        static const TypeCode_ptr _tc_Contained;
        class OBBEXPDLL Contained : public virtual  IRObject
         {
            public:


                struct OBBEXPDLL Description {


                     DefinitionKind kind;
                     Any value;
                    Description &operator=(const Description &_obj);
                };
                typedef	Description *	Description_ptr;
                class OBBEXPDLL Description_var
                {
                    public:
                        inline Description_var() {_ptr = 0;}
                        inline Description_var(Description *_obj) {_ptr = _obj;}
                        Description_var(const Description_var &_obj) {_ptr = 0; *this = _obj;}
                        ~Description_var();
                        Description_var &operator=(Description *);
                        Description_var &operator=(const Description_var &);
                        inline Description *operator->() {return _ptr;}
                        inline const Description *operator->() const {return _ptr;}
                        inline const Description & in () const { return *_ptr; }
                        inline Description & inout () { return *_ptr; }
                        Description *& out ()
                        {
                            delete _ptr;
                            _ptr=0;
                            return _ptr;
                        }
                        Description * _retn ()
                        {
                            Description *tmp = _ptr;
                            _ptr = 0;
                            return tmp;
                        }
                        inline Description_ptr & ptr() { return _ptr; }
                        inline operator Description&() { return *_ptr; }
                        inline operator const Description&() const { return *_ptr; }
                        inline operator Description_ptr &() { return _ptr; }
                    private:
                        Description *_ptr;
                };  // class Description_var

                class OBBEXPDLL Description_out
                {
                    public:
                        Description_out (Description *& p) : ptr_(p) { ptr_ = 0; }
                        Description_out (Description_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        Description_out (const Description_out & a) : ptr_(a.ptr_) {}
                        Description_out & operator=(const Description_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        Description_out & operator=(Description * p) {
                            ptr_ = p; return *this; }
                        inline operator Description_ptr & () { return ptr_; }
                        inline Description_ptr & ptr () { return ptr_; }
                        inline Description_ptr operator->() { return ptr_; }
                    private:
                        Description_ptr & ptr_;
                        void operator=(const Description_var &);

                };  // class Description_out
                static const TypeCode_ptr _tc_Description;
                static Contained_ptr _duplicate(Contained_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Contained_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static Contained_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Description * describe (); 

                virtual void move (
                    Container_ptr new_container,
                    const char * new_name,
                    const char * new_version); 

                virtual RepositoryId id (); 

                virtual void id (
                    const char * id); 

                virtual Identifier name (); 

                virtual void name (
                    const char * name); 

                virtual VersionSpec version (); 

                virtual void version (
                    const char * version); 

                virtual Container_ptr defined_in (); 

                virtual ScopedName absolute_name (); 

                virtual Repository_ptr containing_repository (); 

            protected:
                Contained(Object_ptr obj = 0);
                virtual ~Contained(){ }

            private:
                Contained( const Contained&) { }
                void operator=(const Contained&) { }
                ORB_ptr pORB;
        };  // class Contained



        class OBBEXPDLL Contained_out
         {
            public:
                Contained_out (Contained_ptr & p);
                Contained_out (Contained_var & p);
                Contained_out (const Contained_out & p) : ptr_(p.ptr_) {}
                Contained_out & operator=(const Contained_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Contained_out & operator=(const Contained_var & a);
                Contained_out & operator=(Contained_ptr p) {
                ptr_ = p; return *this;}
                inline operator Contained_ptr & () { return ptr_; }
                inline Contained_ptr & ptr () { return ptr_; }
                inline Contained_ptr operator->() { return ptr_; }
            private:
                Contained_ptr & ptr_;
        };  // class Contained_out



        class OBBEXPDLL InterfaceDefSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(InterfaceDef_ptr _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(InterfaceDef_ptr _ptr);
                        operator InterfaceDef_ptr() const;
                        operator InterfaceDef_ptr &();
                        InterfaceDef_ptr operator->();

                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static InterfaceDef_ptr allocbuf(ULong _nelems);
                        static void freebuf(InterfaceDef_ptr _ptr);

                    private:
                        InterfaceDef_ptr _data;
                        Boolean _release;
                };  // class _ForSeq_var

                InterfaceDefSeq();

                InterfaceDefSeq(ULong _max);

                InterfaceDefSeq
                (
                    ULong _max,
                    ULong _length,
                    InterfaceDef_ptr *_value,
                    Boolean _relse = CORBA_FALSE
                );

                InterfaceDefSeq(const InterfaceDefSeq &_ptr);

                ~InterfaceDefSeq();

                InterfaceDefSeq &operator=(const InterfaceDefSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static InterfaceDef_ptr *allocbuf(ULong _nelems);
                static void freebuf(InterfaceDef_ptr *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class InterfaceDefSeq

        typedef	InterfaceDefSeq *	InterfaceDefSeq_ptr;
        class OBBEXPDLL InterfaceDefSeq_var
        {
            public:
                inline InterfaceDefSeq_var() {_ptr = 0;}
                inline InterfaceDefSeq_var(InterfaceDefSeq *_obj) {_ptr = _obj;}
                InterfaceDefSeq_var(const InterfaceDefSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~InterfaceDefSeq_var();
                InterfaceDefSeq_var &operator=(InterfaceDefSeq *);
                InterfaceDefSeq_var &operator=(const InterfaceDefSeq_var &);
                inline InterfaceDefSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline InterfaceDefSeq *operator->() {return _ptr;}
                inline const InterfaceDefSeq *operator->() const {return _ptr;}
                inline const InterfaceDefSeq & in () const { return *_ptr; }
                inline InterfaceDefSeq & inout () { return *_ptr; }
                InterfaceDefSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InterfaceDefSeq * _retn ()
                {
                    InterfaceDefSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InterfaceDefSeq_ptr & ptr() { return _ptr; }
                inline operator InterfaceDefSeq&() { return *_ptr; }
                inline operator const InterfaceDefSeq&() const { return *_ptr; }
                inline operator InterfaceDefSeq_ptr &() { return _ptr; }
            private:
                InterfaceDefSeq *_ptr;
        };  // class InterfaceDefSeq_var

        class OBBEXPDLL InterfaceDefSeq_out
        {
            public:
                InterfaceDefSeq_out (InterfaceDefSeq *& p) : ptr_(p) { ptr_ = 0; }
                InterfaceDefSeq_out (InterfaceDefSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InterfaceDefSeq_out (const InterfaceDefSeq_out & a) : ptr_(a.ptr_) {}
                InterfaceDefSeq_out & operator=(const InterfaceDefSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InterfaceDefSeq_out & operator=(InterfaceDefSeq * p) {
                    ptr_ = p; return *this; }
                inline operator InterfaceDefSeq_ptr & () { return ptr_; }
                inline InterfaceDefSeq_ptr & ptr () { return ptr_; }
                inline InterfaceDefSeq_ptr operator->() { return ptr_; }
                inline InterfaceDefSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                InterfaceDefSeq_ptr & ptr_;
                void operator=(const InterfaceDefSeq_var &);

        };  // class InterfaceDefSeq_out
        static const TypeCode_ptr _tc_InterfaceDefSeq;


        class OBBEXPDLL ValueDefSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(ValueDef_ptr _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(ValueDef_ptr _ptr);
                        operator ValueDef_ptr() const;
                        operator ValueDef_ptr &();
                        ValueDef_ptr operator->();

                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static ValueDef_ptr allocbuf(ULong _nelems);
                        static void freebuf(ValueDef_ptr _ptr);

                    private:
                        ValueDef_ptr _data;
                        Boolean _release;
                };  // class _ForSeq_var

                ValueDefSeq();

                ValueDefSeq(ULong _max);

                ValueDefSeq
                (
                    ULong _max,
                    ULong _length,
                    ValueDef_ptr *_value,
                    Boolean _relse = CORBA_FALSE
                );

                ValueDefSeq(const ValueDefSeq &_ptr);

                ~ValueDefSeq();

                ValueDefSeq &operator=(const ValueDefSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static ValueDef_ptr *allocbuf(ULong _nelems);
                static void freebuf(ValueDef_ptr *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class ValueDefSeq

        typedef	ValueDefSeq *	ValueDefSeq_ptr;
        class OBBEXPDLL ValueDefSeq_var
        {
            public:
                inline ValueDefSeq_var() {_ptr = 0;}
                inline ValueDefSeq_var(ValueDefSeq *_obj) {_ptr = _obj;}
                ValueDefSeq_var(const ValueDefSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~ValueDefSeq_var();
                ValueDefSeq_var &operator=(ValueDefSeq *);
                ValueDefSeq_var &operator=(const ValueDefSeq_var &);
                inline ValueDefSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline ValueDefSeq *operator->() {return _ptr;}
                inline const ValueDefSeq *operator->() const {return _ptr;}
                inline const ValueDefSeq & in () const { return *_ptr; }
                inline ValueDefSeq & inout () { return *_ptr; }
                ValueDefSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ValueDefSeq * _retn ()
                {
                    ValueDefSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ValueDefSeq_ptr & ptr() { return _ptr; }
                inline operator ValueDefSeq&() { return *_ptr; }
                inline operator const ValueDefSeq&() const { return *_ptr; }
                inline operator ValueDefSeq_ptr &() { return _ptr; }
            private:
                ValueDefSeq *_ptr;
        };  // class ValueDefSeq_var

        class OBBEXPDLL ValueDefSeq_out
        {
            public:
                ValueDefSeq_out (ValueDefSeq *& p) : ptr_(p) { ptr_ = 0; }
                ValueDefSeq_out (ValueDefSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ValueDefSeq_out (const ValueDefSeq_out & a) : ptr_(a.ptr_) {}
                ValueDefSeq_out & operator=(const ValueDefSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ValueDefSeq_out & operator=(ValueDefSeq * p) {
                    ptr_ = p; return *this; }
                inline operator ValueDefSeq_ptr & () { return ptr_; }
                inline ValueDefSeq_ptr & ptr () { return ptr_; }
                inline ValueDefSeq_ptr operator->() { return ptr_; }
                inline ValueDefSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                ValueDefSeq_ptr & ptr_;
                void operator=(const ValueDefSeq_var &);

        };  // class ValueDefSeq_out
        static const TypeCode_ptr _tc_ValueDefSeq;


        class OBBEXPDLL AbstractInterfaceDefSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(AbstractInterfaceDef_ptr _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(AbstractInterfaceDef_ptr _ptr);
                        operator AbstractInterfaceDef_ptr() const;
                        operator AbstractInterfaceDef_ptr &();
                        AbstractInterfaceDef_ptr operator->();

                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static AbstractInterfaceDef_ptr allocbuf(ULong _nelems);
                        static void freebuf(AbstractInterfaceDef_ptr _ptr);

                    private:
                        AbstractInterfaceDef_ptr _data;
                        Boolean _release;
                };  // class _ForSeq_var

                AbstractInterfaceDefSeq();

                AbstractInterfaceDefSeq(ULong _max);

                AbstractInterfaceDefSeq
                (
                    ULong _max,
                    ULong _length,
                    AbstractInterfaceDef_ptr *_value,
                    Boolean _relse = CORBA_FALSE
                );

                AbstractInterfaceDefSeq(const AbstractInterfaceDefSeq &_ptr);

                ~AbstractInterfaceDefSeq();

                AbstractInterfaceDefSeq &operator=(const AbstractInterfaceDefSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static AbstractInterfaceDef_ptr *allocbuf(ULong _nelems);
                static void freebuf(AbstractInterfaceDef_ptr *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class AbstractInterfaceDefSeq

        typedef	AbstractInterfaceDefSeq *	AbstractInterfaceDefSeq_ptr;
        class OBBEXPDLL AbstractInterfaceDefSeq_var
        {
            public:
                inline AbstractInterfaceDefSeq_var() {_ptr = 0;}
                inline AbstractInterfaceDefSeq_var(AbstractInterfaceDefSeq *_obj) {_ptr = _obj;}
                AbstractInterfaceDefSeq_var(const AbstractInterfaceDefSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~AbstractInterfaceDefSeq_var();
                AbstractInterfaceDefSeq_var &operator=(AbstractInterfaceDefSeq *);
                AbstractInterfaceDefSeq_var &operator=(const AbstractInterfaceDefSeq_var &);
                inline AbstractInterfaceDefSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline AbstractInterfaceDefSeq *operator->() {return _ptr;}
                inline const AbstractInterfaceDefSeq *operator->() const {return _ptr;}
                inline const AbstractInterfaceDefSeq & in () const { return *_ptr; }
                inline AbstractInterfaceDefSeq & inout () { return *_ptr; }
                AbstractInterfaceDefSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                AbstractInterfaceDefSeq * _retn ()
                {
                    AbstractInterfaceDefSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline AbstractInterfaceDefSeq_ptr & ptr() { return _ptr; }
                inline operator AbstractInterfaceDefSeq&() { return *_ptr; }
                inline operator const AbstractInterfaceDefSeq&() const { return *_ptr; }
                inline operator AbstractInterfaceDefSeq_ptr &() { return _ptr; }
            private:
                AbstractInterfaceDefSeq *_ptr;
        };  // class AbstractInterfaceDefSeq_var

        class OBBEXPDLL AbstractInterfaceDefSeq_out
        {
            public:
                AbstractInterfaceDefSeq_out (AbstractInterfaceDefSeq *& p) : ptr_(p) { ptr_ = 0; }
                AbstractInterfaceDefSeq_out (AbstractInterfaceDefSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                AbstractInterfaceDefSeq_out (const AbstractInterfaceDefSeq_out & a) : ptr_(a.ptr_) {}
                AbstractInterfaceDefSeq_out & operator=(const AbstractInterfaceDefSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                AbstractInterfaceDefSeq_out & operator=(AbstractInterfaceDefSeq * p) {
                    ptr_ = p; return *this; }
                inline operator AbstractInterfaceDefSeq_ptr & () { return ptr_; }
                inline AbstractInterfaceDefSeq_ptr & ptr () { return ptr_; }
                inline AbstractInterfaceDefSeq_ptr operator->() { return ptr_; }
                inline AbstractInterfaceDefSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                AbstractInterfaceDefSeq_ptr & ptr_;
                void operator=(const AbstractInterfaceDefSeq_var &);

        };  // class AbstractInterfaceDefSeq_out
        static const TypeCode_ptr _tc_AbstractInterfaceDefSeq;


        class OBBEXPDLL LocalInterfaceDefSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(LocalInterfaceDef_ptr _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(LocalInterfaceDef_ptr _ptr);
                        operator LocalInterfaceDef_ptr() const;
                        operator LocalInterfaceDef_ptr &();
                        LocalInterfaceDef_ptr operator->();

                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static LocalInterfaceDef_ptr allocbuf(ULong _nelems);
                        static void freebuf(LocalInterfaceDef_ptr _ptr);

                    private:
                        LocalInterfaceDef_ptr _data;
                        Boolean _release;
                };  // class _ForSeq_var

                LocalInterfaceDefSeq();

                LocalInterfaceDefSeq(ULong _max);

                LocalInterfaceDefSeq
                (
                    ULong _max,
                    ULong _length,
                    LocalInterfaceDef_ptr *_value,
                    Boolean _relse = CORBA_FALSE
                );

                LocalInterfaceDefSeq(const LocalInterfaceDefSeq &_ptr);

                ~LocalInterfaceDefSeq();

                LocalInterfaceDefSeq &operator=(const LocalInterfaceDefSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static LocalInterfaceDef_ptr *allocbuf(ULong _nelems);
                static void freebuf(LocalInterfaceDef_ptr *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class LocalInterfaceDefSeq

        typedef	LocalInterfaceDefSeq *	LocalInterfaceDefSeq_ptr;
        class OBBEXPDLL LocalInterfaceDefSeq_var
        {
            public:
                inline LocalInterfaceDefSeq_var() {_ptr = 0;}
                inline LocalInterfaceDefSeq_var(LocalInterfaceDefSeq *_obj) {_ptr = _obj;}
                LocalInterfaceDefSeq_var(const LocalInterfaceDefSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~LocalInterfaceDefSeq_var();
                LocalInterfaceDefSeq_var &operator=(LocalInterfaceDefSeq *);
                LocalInterfaceDefSeq_var &operator=(const LocalInterfaceDefSeq_var &);
                inline LocalInterfaceDefSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline LocalInterfaceDefSeq *operator->() {return _ptr;}
                inline const LocalInterfaceDefSeq *operator->() const {return _ptr;}
                inline const LocalInterfaceDefSeq & in () const { return *_ptr; }
                inline LocalInterfaceDefSeq & inout () { return *_ptr; }
                LocalInterfaceDefSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                LocalInterfaceDefSeq * _retn ()
                {
                    LocalInterfaceDefSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline LocalInterfaceDefSeq_ptr & ptr() { return _ptr; }
                inline operator LocalInterfaceDefSeq&() { return *_ptr; }
                inline operator const LocalInterfaceDefSeq&() const { return *_ptr; }
                inline operator LocalInterfaceDefSeq_ptr &() { return _ptr; }
            private:
                LocalInterfaceDefSeq *_ptr;
        };  // class LocalInterfaceDefSeq_var

        class OBBEXPDLL LocalInterfaceDefSeq_out
        {
            public:
                LocalInterfaceDefSeq_out (LocalInterfaceDefSeq *& p) : ptr_(p) { ptr_ = 0; }
                LocalInterfaceDefSeq_out (LocalInterfaceDefSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                LocalInterfaceDefSeq_out (const LocalInterfaceDefSeq_out & a) : ptr_(a.ptr_) {}
                LocalInterfaceDefSeq_out & operator=(const LocalInterfaceDefSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                LocalInterfaceDefSeq_out & operator=(LocalInterfaceDefSeq * p) {
                    ptr_ = p; return *this; }
                inline operator LocalInterfaceDefSeq_ptr & () { return ptr_; }
                inline LocalInterfaceDefSeq_ptr & ptr () { return ptr_; }
                inline LocalInterfaceDefSeq_ptr operator->() { return ptr_; }
                inline LocalInterfaceDefSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                LocalInterfaceDefSeq_ptr & ptr_;
                void operator=(const LocalInterfaceDefSeq_var &);

        };  // class LocalInterfaceDefSeq_out
        static const TypeCode_ptr _tc_LocalInterfaceDefSeq;


        class OBBEXPDLL ContainedSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(Contained_ptr _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(Contained_ptr _ptr);
                        operator Contained_ptr() const;
                        operator Contained_ptr &();
                        Contained_ptr operator->();

                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static Contained_ptr allocbuf(ULong _nelems);
                        static void freebuf(Contained_ptr _ptr);

                    private:
                        Contained_ptr _data;
                        Boolean _release;
                };  // class _ForSeq_var

                ContainedSeq();

                ContainedSeq(ULong _max);

                ContainedSeq
                (
                    ULong _max,
                    ULong _length,
                    Contained_ptr *_value,
                    Boolean _relse = CORBA_FALSE
                );

                ContainedSeq(const ContainedSeq &_ptr);

                ~ContainedSeq();

                ContainedSeq &operator=(const ContainedSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static Contained_ptr *allocbuf(ULong _nelems);
                static void freebuf(Contained_ptr *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class ContainedSeq

        typedef	ContainedSeq *	ContainedSeq_ptr;
        class OBBEXPDLL ContainedSeq_var
        {
            public:
                inline ContainedSeq_var() {_ptr = 0;}
                inline ContainedSeq_var(ContainedSeq *_obj) {_ptr = _obj;}
                ContainedSeq_var(const ContainedSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~ContainedSeq_var();
                ContainedSeq_var &operator=(ContainedSeq *);
                ContainedSeq_var &operator=(const ContainedSeq_var &);
                inline ContainedSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline ContainedSeq *operator->() {return _ptr;}
                inline const ContainedSeq *operator->() const {return _ptr;}
                inline const ContainedSeq & in () const { return *_ptr; }
                inline ContainedSeq & inout () { return *_ptr; }
                ContainedSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ContainedSeq * _retn ()
                {
                    ContainedSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ContainedSeq_ptr & ptr() { return _ptr; }
                inline operator ContainedSeq&() { return *_ptr; }
                inline operator const ContainedSeq&() const { return *_ptr; }
                inline operator ContainedSeq_ptr &() { return _ptr; }
            private:
                ContainedSeq *_ptr;
        };  // class ContainedSeq_var

        class OBBEXPDLL ContainedSeq_out
        {
            public:
                ContainedSeq_out (ContainedSeq *& p) : ptr_(p) { ptr_ = 0; }
                ContainedSeq_out (ContainedSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ContainedSeq_out (const ContainedSeq_out & a) : ptr_(a.ptr_) {}
                ContainedSeq_out & operator=(const ContainedSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ContainedSeq_out & operator=(ContainedSeq * p) {
                    ptr_ = p; return *this; }
                inline operator ContainedSeq_ptr & () { return ptr_; }
                inline ContainedSeq_ptr & ptr () { return ptr_; }
                inline ContainedSeq_ptr operator->() { return ptr_; }
                inline ContainedSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                ContainedSeq_ptr & ptr_;
                void operator=(const ContainedSeq_var &);

        };  // class ContainedSeq_out
        static const TypeCode_ptr _tc_ContainedSeq;


        struct OBBEXPDLL StructMember {
            String_var name;


             TypeCode_var type;


             IDLType_var type_def;
            StructMember &operator=(const StructMember &_obj);
        };
        typedef	StructMember *	StructMember_ptr;
        class OBBEXPDLL StructMember_var
        {
            public:
                inline StructMember_var() {_ptr = 0;}
                inline StructMember_var(StructMember *_obj) {_ptr = _obj;}
                StructMember_var(const StructMember_var &_obj) {_ptr = 0; *this = _obj;}
                ~StructMember_var();
                StructMember_var &operator=(StructMember *);
                StructMember_var &operator=(const StructMember_var &);
                inline StructMember *operator->() {return _ptr;}
                inline const StructMember *operator->() const {return _ptr;}
                inline const StructMember & in () const { return *_ptr; }
                inline StructMember & inout () { return *_ptr; }
                StructMember *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                StructMember * _retn ()
                {
                    StructMember *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline StructMember_ptr & ptr() { return _ptr; }
                inline operator StructMember&() { return *_ptr; }
                inline operator const StructMember&() const { return *_ptr; }
                inline operator StructMember_ptr &() { return _ptr; }
            private:
                StructMember *_ptr;
        };  // class StructMember_var

        class OBBEXPDLL StructMember_out
        {
            public:
                StructMember_out (StructMember *& p) : ptr_(p) { ptr_ = 0; }
                StructMember_out (StructMember_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                StructMember_out (const StructMember_out & a) : ptr_(a.ptr_) {}
                StructMember_out & operator=(const StructMember_out & a) {
                    ptr_ = a.ptr_; return *this; }
                StructMember_out & operator=(StructMember * p) {
                    ptr_ = p; return *this; }
                inline operator StructMember_ptr & () { return ptr_; }
                inline StructMember_ptr & ptr () { return ptr_; }
                inline StructMember_ptr operator->() { return ptr_; }
            private:
                StructMember_ptr & ptr_;
                void operator=(const StructMember_var &);

        };  // class StructMember_out
        static const TypeCode_ptr _tc_StructMember;


        class OBBEXPDLL StructMemberSeq
        {
            public:
                StructMemberSeq();

                StructMemberSeq(ULong _max);

                StructMemberSeq
                (
                    ULong _max,
                    ULong _length,
                    StructMember *_value,
                    Boolean _relse = CORBA_FALSE
                );

                StructMemberSeq(const StructMemberSeq &_ptr);

                ~StructMemberSeq();

                StructMemberSeq &operator=(const StructMemberSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline StructMember &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const StructMember &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const StructMember &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static StructMember *allocbuf(ULong _nelems);
                static void freebuf(StructMember *_ptr);

                inline StructMember * OBB__GetData() { return _data; }
            private:
                StructMember *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class StructMemberSeq

        typedef	StructMemberSeq *	StructMemberSeq_ptr;
        class OBBEXPDLL StructMemberSeq_var
        {
            public:
                inline StructMemberSeq_var() {_ptr = 0;}
                inline StructMemberSeq_var(StructMemberSeq *_obj) {_ptr = _obj;}
                StructMemberSeq_var(const StructMemberSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~StructMemberSeq_var();
                StructMemberSeq_var &operator=(StructMemberSeq *);
                StructMemberSeq_var &operator=(const StructMemberSeq_var &);
                inline StructMember &operator[](ULong _index) {return (*_ptr)[_index];}
                inline StructMemberSeq *operator->() {return _ptr;}
                inline const StructMemberSeq *operator->() const {return _ptr;}
                inline const StructMemberSeq & in () const { return *_ptr; }
                inline StructMemberSeq & inout () { return *_ptr; }
                StructMemberSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                StructMemberSeq * _retn ()
                {
                    StructMemberSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline StructMemberSeq_ptr & ptr() { return _ptr; }
                inline operator StructMemberSeq&() { return *_ptr; }
                inline operator const StructMemberSeq&() const { return *_ptr; }
                inline operator StructMemberSeq_ptr &() { return _ptr; }
            private:
                StructMemberSeq *_ptr;
        };  // class StructMemberSeq_var

        class OBBEXPDLL StructMemberSeq_out
        {
            public:
                StructMemberSeq_out (StructMemberSeq *& p) : ptr_(p) { ptr_ = 0; }
                StructMemberSeq_out (StructMemberSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                StructMemberSeq_out (const StructMemberSeq_out & a) : ptr_(a.ptr_) {}
                StructMemberSeq_out & operator=(const StructMemberSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                StructMemberSeq_out & operator=(StructMemberSeq * p) {
                    ptr_ = p; return *this; }
                inline operator StructMemberSeq_ptr & () { return ptr_; }
                inline StructMemberSeq_ptr & ptr () { return ptr_; }
                inline StructMemberSeq_ptr operator->() { return ptr_; }
                inline StructMember & operator[](ULong _index) {return (*ptr_)[_index]; }
            private:
                StructMemberSeq_ptr & ptr_;
                void operator=(const StructMemberSeq_var &);

        };  // class StructMemberSeq_out
        static const TypeCode_ptr _tc_StructMemberSeq;


        struct OBBEXPDLL Initializer {


             StructMemberSeq members;
            String_var name;
            Initializer &operator=(const Initializer &_obj);
        };
        typedef	Initializer *	Initializer_ptr;
        class OBBEXPDLL Initializer_var
        {
            public:
                inline Initializer_var() {_ptr = 0;}
                inline Initializer_var(Initializer *_obj) {_ptr = _obj;}
                Initializer_var(const Initializer_var &_obj) {_ptr = 0; *this = _obj;}
                ~Initializer_var();
                Initializer_var &operator=(Initializer *);
                Initializer_var &operator=(const Initializer_var &);
                inline Initializer *operator->() {return _ptr;}
                inline const Initializer *operator->() const {return _ptr;}
                inline const Initializer & in () const { return *_ptr; }
                inline Initializer & inout () { return *_ptr; }
                Initializer *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                Initializer * _retn ()
                {
                    Initializer *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline Initializer_ptr & ptr() { return _ptr; }
                inline operator Initializer&() { return *_ptr; }
                inline operator const Initializer&() const { return *_ptr; }
                inline operator Initializer_ptr &() { return _ptr; }
            private:
                Initializer *_ptr;
        };  // class Initializer_var

        class OBBEXPDLL Initializer_out
        {
            public:
                Initializer_out (Initializer *& p) : ptr_(p) { ptr_ = 0; }
                Initializer_out (Initializer_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                Initializer_out (const Initializer_out & a) : ptr_(a.ptr_) {}
                Initializer_out & operator=(const Initializer_out & a) {
                    ptr_ = a.ptr_; return *this; }
                Initializer_out & operator=(Initializer * p) {
                    ptr_ = p; return *this; }
                inline operator Initializer_ptr & () { return ptr_; }
                inline Initializer_ptr & ptr () { return ptr_; }
                inline Initializer_ptr operator->() { return ptr_; }
            private:
                Initializer_ptr & ptr_;
                void operator=(const Initializer_var &);

        };  // class Initializer_out
        static const TypeCode_ptr _tc_Initializer;


        class OBBEXPDLL InitializerSeq
        {
            public:
                InitializerSeq();

                InitializerSeq(ULong _max);

                InitializerSeq
                (
                    ULong _max,
                    ULong _length,
                    Initializer *_value,
                    Boolean _relse = CORBA_FALSE
                );

                InitializerSeq(const InitializerSeq &_ptr);

                ~InitializerSeq();

                InitializerSeq &operator=(const InitializerSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline Initializer &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const Initializer &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const Initializer &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static Initializer *allocbuf(ULong _nelems);
                static void freebuf(Initializer *_ptr);

                inline Initializer * OBB__GetData() { return _data; }
            private:
                Initializer *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class InitializerSeq

        typedef	InitializerSeq *	InitializerSeq_ptr;
        class OBBEXPDLL InitializerSeq_var
        {
            public:
                inline InitializerSeq_var() {_ptr = 0;}
                inline InitializerSeq_var(InitializerSeq *_obj) {_ptr = _obj;}
                InitializerSeq_var(const InitializerSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~InitializerSeq_var();
                InitializerSeq_var &operator=(InitializerSeq *);
                InitializerSeq_var &operator=(const InitializerSeq_var &);
                inline Initializer &operator[](ULong _index) {return (*_ptr)[_index];}
                inline InitializerSeq *operator->() {return _ptr;}
                inline const InitializerSeq *operator->() const {return _ptr;}
                inline const InitializerSeq & in () const { return *_ptr; }
                inline InitializerSeq & inout () { return *_ptr; }
                InitializerSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InitializerSeq * _retn ()
                {
                    InitializerSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InitializerSeq_ptr & ptr() { return _ptr; }
                inline operator InitializerSeq&() { return *_ptr; }
                inline operator const InitializerSeq&() const { return *_ptr; }
                inline operator InitializerSeq_ptr &() { return _ptr; }
            private:
                InitializerSeq *_ptr;
        };  // class InitializerSeq_var

        class OBBEXPDLL InitializerSeq_out
        {
            public:
                InitializerSeq_out (InitializerSeq *& p) : ptr_(p) { ptr_ = 0; }
                InitializerSeq_out (InitializerSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InitializerSeq_out (const InitializerSeq_out & a) : ptr_(a.ptr_) {}
                InitializerSeq_out & operator=(const InitializerSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InitializerSeq_out & operator=(InitializerSeq * p) {
                    ptr_ = p; return *this; }
                inline operator InitializerSeq_ptr & () { return ptr_; }
                inline InitializerSeq_ptr & ptr () { return ptr_; }
                inline InitializerSeq_ptr operator->() { return ptr_; }
                inline Initializer & operator[](ULong _index) {return (*ptr_)[_index]; }
            private:
                InitializerSeq_ptr & ptr_;
                void operator=(const InitializerSeq_var &);

        };  // class InitializerSeq_out
        static const TypeCode_ptr _tc_InitializerSeq;


        struct OBBEXPDLL UnionMember {
            String_var name;
             Any label;


             TypeCode_var type;


             IDLType_var type_def;
            UnionMember &operator=(const UnionMember &_obj);
        };
        typedef	UnionMember *	UnionMember_ptr;
        class OBBEXPDLL UnionMember_var
        {
            public:
                inline UnionMember_var() {_ptr = 0;}
                inline UnionMember_var(UnionMember *_obj) {_ptr = _obj;}
                UnionMember_var(const UnionMember_var &_obj) {_ptr = 0; *this = _obj;}
                ~UnionMember_var();
                UnionMember_var &operator=(UnionMember *);
                UnionMember_var &operator=(const UnionMember_var &);
                inline UnionMember *operator->() {return _ptr;}
                inline const UnionMember *operator->() const {return _ptr;}
                inline const UnionMember & in () const { return *_ptr; }
                inline UnionMember & inout () { return *_ptr; }
                UnionMember *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                UnionMember * _retn ()
                {
                    UnionMember *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline UnionMember_ptr & ptr() { return _ptr; }
                inline operator UnionMember&() { return *_ptr; }
                inline operator const UnionMember&() const { return *_ptr; }
                inline operator UnionMember_ptr &() { return _ptr; }
            private:
                UnionMember *_ptr;
        };  // class UnionMember_var

        class OBBEXPDLL UnionMember_out
        {
            public:
                UnionMember_out (UnionMember *& p) : ptr_(p) { ptr_ = 0; }
                UnionMember_out (UnionMember_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                UnionMember_out (const UnionMember_out & a) : ptr_(a.ptr_) {}
                UnionMember_out & operator=(const UnionMember_out & a) {
                    ptr_ = a.ptr_; return *this; }
                UnionMember_out & operator=(UnionMember * p) {
                    ptr_ = p; return *this; }
                inline operator UnionMember_ptr & () { return ptr_; }
                inline UnionMember_ptr & ptr () { return ptr_; }
                inline UnionMember_ptr operator->() { return ptr_; }
            private:
                UnionMember_ptr & ptr_;
                void operator=(const UnionMember_var &);

        };  // class UnionMember_out
        static const TypeCode_ptr _tc_UnionMember;


        class OBBEXPDLL UnionMemberSeq
        {
            public:
                UnionMemberSeq();

                UnionMemberSeq(ULong _max);

                UnionMemberSeq
                (
                    ULong _max,
                    ULong _length,
                    UnionMember *_value,
                    Boolean _relse = CORBA_FALSE
                );

                UnionMemberSeq(const UnionMemberSeq &_ptr);

                ~UnionMemberSeq();

                UnionMemberSeq &operator=(const UnionMemberSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline UnionMember &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const UnionMember &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const UnionMember &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static UnionMember *allocbuf(ULong _nelems);
                static void freebuf(UnionMember *_ptr);

                inline UnionMember * OBB__GetData() { return _data; }
            private:
                UnionMember *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class UnionMemberSeq

        typedef	UnionMemberSeq *	UnionMemberSeq_ptr;
        class OBBEXPDLL UnionMemberSeq_var
        {
            public:
                inline UnionMemberSeq_var() {_ptr = 0;}
                inline UnionMemberSeq_var(UnionMemberSeq *_obj) {_ptr = _obj;}
                UnionMemberSeq_var(const UnionMemberSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~UnionMemberSeq_var();
                UnionMemberSeq_var &operator=(UnionMemberSeq *);
                UnionMemberSeq_var &operator=(const UnionMemberSeq_var &);
                inline UnionMember &operator[](ULong _index) {return (*_ptr)[_index];}
                inline UnionMemberSeq *operator->() {return _ptr;}
                inline const UnionMemberSeq *operator->() const {return _ptr;}
                inline const UnionMemberSeq & in () const { return *_ptr; }
                inline UnionMemberSeq & inout () { return *_ptr; }
                UnionMemberSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                UnionMemberSeq * _retn ()
                {
                    UnionMemberSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline UnionMemberSeq_ptr & ptr() { return _ptr; }
                inline operator UnionMemberSeq&() { return *_ptr; }
                inline operator const UnionMemberSeq&() const { return *_ptr; }
                inline operator UnionMemberSeq_ptr &() { return _ptr; }
            private:
                UnionMemberSeq *_ptr;
        };  // class UnionMemberSeq_var

        class OBBEXPDLL UnionMemberSeq_out
        {
            public:
                UnionMemberSeq_out (UnionMemberSeq *& p) : ptr_(p) { ptr_ = 0; }
                UnionMemberSeq_out (UnionMemberSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                UnionMemberSeq_out (const UnionMemberSeq_out & a) : ptr_(a.ptr_) {}
                UnionMemberSeq_out & operator=(const UnionMemberSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                UnionMemberSeq_out & operator=(UnionMemberSeq * p) {
                    ptr_ = p; return *this; }
                inline operator UnionMemberSeq_ptr & () { return ptr_; }
                inline UnionMemberSeq_ptr & ptr () { return ptr_; }
                inline UnionMemberSeq_ptr operator->() { return ptr_; }
                inline UnionMember & operator[](ULong _index) {return (*ptr_)[_index]; }
            private:
                UnionMemberSeq_ptr & ptr_;
                void operator=(const UnionMemberSeq_var &);

        };  // class UnionMemberSeq_out
        static const TypeCode_ptr _tc_UnionMemberSeq;


        class OBBEXPDLL EnumMemberSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(Identifier _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(Identifier _ptr);
                        operator Identifier() const;
                        operator Identifier ();
                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static Identifier allocbuf(ULong _nelems);
                        static void freebuf(Identifier _ptr);

                    private:
                        Identifier _data;
                        Boolean _release;
                };  // class _ForSeq_var

                EnumMemberSeq();

                EnumMemberSeq(ULong _max);

                EnumMemberSeq
                (
                    ULong _max,
                    ULong _length,
                    Identifier *_value,
                    Boolean _relse = CORBA_FALSE
                );

                EnumMemberSeq(const EnumMemberSeq &_ptr);

                ~EnumMemberSeq();

                EnumMemberSeq &operator=(const EnumMemberSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static Identifier *allocbuf(ULong _nelems);
                static void freebuf(Identifier *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class EnumMemberSeq

        typedef	EnumMemberSeq *	EnumMemberSeq_ptr;
        class OBBEXPDLL EnumMemberSeq_var
        {
            public:
                inline EnumMemberSeq_var() {_ptr = 0;}
                inline EnumMemberSeq_var(EnumMemberSeq *_obj) {_ptr = _obj;}
                EnumMemberSeq_var(const EnumMemberSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~EnumMemberSeq_var();
                EnumMemberSeq_var &operator=(EnumMemberSeq *);
                EnumMemberSeq_var &operator=(const EnumMemberSeq_var &);
                inline EnumMemberSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline EnumMemberSeq *operator->() {return _ptr;}
                inline const EnumMemberSeq *operator->() const {return _ptr;}
                inline const EnumMemberSeq & in () const { return *_ptr; }
                inline EnumMemberSeq & inout () { return *_ptr; }
                EnumMemberSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                EnumMemberSeq * _retn ()
                {
                    EnumMemberSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline EnumMemberSeq_ptr & ptr() { return _ptr; }
                inline operator EnumMemberSeq&() { return *_ptr; }
                inline operator const EnumMemberSeq&() const { return *_ptr; }
                inline operator EnumMemberSeq_ptr &() { return _ptr; }
            private:
                EnumMemberSeq *_ptr;
        };  // class EnumMemberSeq_var

        class OBBEXPDLL EnumMemberSeq_out
        {
            public:
                EnumMemberSeq_out (EnumMemberSeq *& p) : ptr_(p) { ptr_ = 0; }
                EnumMemberSeq_out (EnumMemberSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                EnumMemberSeq_out (const EnumMemberSeq_out & a) : ptr_(a.ptr_) {}
                EnumMemberSeq_out & operator=(const EnumMemberSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                EnumMemberSeq_out & operator=(EnumMemberSeq * p) {
                    ptr_ = p; return *this; }
                inline operator EnumMemberSeq_ptr & () { return ptr_; }
                inline EnumMemberSeq_ptr & ptr () { return ptr_; }
                inline EnumMemberSeq_ptr operator->() { return ptr_; }
                inline EnumMemberSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                EnumMemberSeq_ptr & ptr_;
                void operator=(const EnumMemberSeq_var &);

        };  // class EnumMemberSeq_out
        static const TypeCode_ptr _tc_EnumMemberSeq;


        static const TypeCode_ptr _tc_Container;
        class OBBEXPDLL Container : public virtual  IRObject
         {
            public:


                struct OBBEXPDLL Description {


                     Contained_var contained_object;


                     DefinitionKind kind;
                     Any value;
                    Description &operator=(const Description &_obj);
                };
                typedef	Description *	Description_ptr;
                class OBBEXPDLL Description_var
                {
                    public:
                        inline Description_var() {_ptr = 0;}
                        inline Description_var(Description *_obj) {_ptr = _obj;}
                        Description_var(const Description_var &_obj) {_ptr = 0; *this = _obj;}
                        ~Description_var();
                        Description_var &operator=(Description *);
                        Description_var &operator=(const Description_var &);
                        inline Description *operator->() {return _ptr;}
                        inline const Description *operator->() const {return _ptr;}
                        inline const Description & in () const { return *_ptr; }
                        inline Description & inout () { return *_ptr; }
                        Description *& out ()
                        {
                            delete _ptr;
                            _ptr=0;
                            return _ptr;
                        }
                        Description * _retn ()
                        {
                            Description *tmp = _ptr;
                            _ptr = 0;
                            return tmp;
                        }
                        inline Description_ptr & ptr() { return _ptr; }
                        inline operator Description&() { return *_ptr; }
                        inline operator const Description&() const { return *_ptr; }
                        inline operator Description_ptr &() { return _ptr; }
                    private:
                        Description *_ptr;
                };  // class Description_var

                class OBBEXPDLL Description_out
                {
                    public:
                        Description_out (Description *& p) : ptr_(p) { ptr_ = 0; }
                        Description_out (Description_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        Description_out (const Description_out & a) : ptr_(a.ptr_) {}
                        Description_out & operator=(const Description_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        Description_out & operator=(Description * p) {
                            ptr_ = p; return *this; }
                        inline operator Description_ptr & () { return ptr_; }
                        inline Description_ptr & ptr () { return ptr_; }
                        inline Description_ptr operator->() { return ptr_; }
                    private:
                        Description_ptr & ptr_;
                        void operator=(const Description_var &);

                };  // class Description_out
                static const TypeCode_ptr _tc_Description;


                class OBBEXPDLL DescriptionSeq
                {
                    public:
                        DescriptionSeq();

                        DescriptionSeq(ULong _max);

                        DescriptionSeq
                        (
                            ULong _max,
                            ULong _length,
                            Description *_value,
                            Boolean _relse = CORBA_FALSE
                        );

                        DescriptionSeq(const DescriptionSeq &_ptr);

                        ~DescriptionSeq();

                        DescriptionSeq &operator=(const DescriptionSeq& _ptr);

                        inline ULong maximum() const {return _maximum;}

                        void length(ULong);
                        inline ULong length() const {return _current;}

                        inline Description &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                        inline const Description &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const Description &)_data[_index];}
#else
                            return _data[_index];}
#endif
                        static Description *allocbuf(ULong _nelems);
                        static void freebuf(Description *_ptr);

                        inline Description * OBB__GetData() { return _data; }
                    private:
                        Description *_data;
                        ULong _maximum;
                        ULong _current;
                        Boolean _release;
                };  // class DescriptionSeq

                typedef	DescriptionSeq *	DescriptionSeq_ptr;
                class OBBEXPDLL DescriptionSeq_var
                {
                    public:
                        inline DescriptionSeq_var() {_ptr = 0;}
                        inline DescriptionSeq_var(DescriptionSeq *_obj) {_ptr = _obj;}
                        DescriptionSeq_var(const DescriptionSeq_var &_obj) {_ptr = 0; *this = _obj;}
                        ~DescriptionSeq_var();
                        DescriptionSeq_var &operator=(DescriptionSeq *);
                        DescriptionSeq_var &operator=(const DescriptionSeq_var &);
                        inline Description &operator[](ULong _index) {return (*_ptr)[_index];}
                        inline DescriptionSeq *operator->() {return _ptr;}
                        inline const DescriptionSeq *operator->() const {return _ptr;}
                        inline const DescriptionSeq & in () const { return *_ptr; }
                        inline DescriptionSeq & inout () { return *_ptr; }
                        DescriptionSeq *& out ()
                        {
                            delete _ptr;
                            _ptr=0;
                            return _ptr;
                        }
                        DescriptionSeq * _retn ()
                        {
                            DescriptionSeq *tmp = _ptr;
                            _ptr = 0;
                            return tmp;
                        }
                        inline DescriptionSeq_ptr & ptr() { return _ptr; }
                        inline operator DescriptionSeq&() { return *_ptr; }
                        inline operator const DescriptionSeq&() const { return *_ptr; }
                        inline operator DescriptionSeq_ptr &() { return _ptr; }
                    private:
                        DescriptionSeq *_ptr;
                };  // class DescriptionSeq_var

                class OBBEXPDLL DescriptionSeq_out
                {
                    public:
                        DescriptionSeq_out (DescriptionSeq *& p) : ptr_(p) { ptr_ = 0; }
                        DescriptionSeq_out (DescriptionSeq_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        DescriptionSeq_out (const DescriptionSeq_out & a) : ptr_(a.ptr_) {}
                        DescriptionSeq_out & operator=(const DescriptionSeq_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        DescriptionSeq_out & operator=(DescriptionSeq * p) {
                            ptr_ = p; return *this; }
                        inline operator DescriptionSeq_ptr & () { return ptr_; }
                        inline DescriptionSeq_ptr & ptr () { return ptr_; }
                        inline DescriptionSeq_ptr operator->() { return ptr_; }
                        inline Description & operator[](ULong _index) {return (*ptr_)[_index]; }
                    private:
                        DescriptionSeq_ptr & ptr_;
                        void operator=(const DescriptionSeq_var &);

                };  // class DescriptionSeq_out
                static const TypeCode_ptr _tc_DescriptionSeq;
                static Container_ptr _duplicate(Container_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Container_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static Container_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Contained_ptr lookup (
                    const char * search_name); 

                virtual ContainedSeq * contents (
                    DefinitionKind limit_type,
                    Boolean exclude_inherited); 

                virtual ContainedSeq * lookup_name (
                    const char * search_name,
                    Long levels_to_search,
                    DefinitionKind limit_type,
                    Boolean exclude_inherited); 

                virtual DescriptionSeq * describe_contents (
                    DefinitionKind limit_type,
                    Boolean exclude_inherited,
                    Long max_returned_objs); 

                virtual ModuleDef_ptr create_module (
                    const char * id,
                    const char * name,
                    const char * version); 

                virtual ConstantDef_ptr create_constant (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr type,
                     const Any & value); 

                virtual StructDef_ptr create_struct (
                    const char * id,
                    const char * name,
                    const char * version,
                     const StructMemberSeq & members); 

                virtual UnionDef_ptr create_union (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr discriminator_type,
                     const UnionMemberSeq & members); 

                virtual EnumDef_ptr create_enum (
                    const char * id,
                    const char * name,
                    const char * version,
                     const EnumMemberSeq & members); 

                virtual AliasDef_ptr create_alias (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr original_type); 

                virtual InterfaceDef_ptr create_interface (
                    const char * id,
                    const char * name,
                    const char * version,
                     const InterfaceDefSeq & base_interfaces); 

                virtual ValueDef_ptr create_value (
                    const char * id,
                    const char * name,
                    const char * version,
                    Boolean is_custom,
                    Boolean is_abstract,
                    ValueDef_ptr base_value,
                    Boolean is_truncatable,
                     const ValueDefSeq & abstract_base_values,
                     const InterfaceDefSeq & supported_interfaces,
                     const InitializerSeq & initializers); 

                virtual ValueBoxDef_ptr create_value_box (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr original_type_def); 

                virtual ExceptionDef_ptr create_exception (
                    const char * id,
                    const char * name,
                    const char * version,
                     const StructMemberSeq & members); 

                virtual NativeDef_ptr create_native (
                    const char * id,
                    const char * name,
                    const char * version); 

                virtual AbstractInterfaceDef_ptr create_abstract_interface (
                    const char * id,
                    const char * name,
                    const char * version,
                     const AbstractInterfaceDefSeq & base_interfaces); 

                virtual LocalInterfaceDef_ptr create_local_interface (
                    const char * id,
                    const char * name,
                    const char * version,
                     const LocalInterfaceDefSeq & base_interfaces); 

            protected:
                Container(Object_ptr obj = 0);
                virtual ~Container(){ }

            private:
                Container( const Container&) { }
                void operator=(const Container&) { }
                ORB_ptr pORB;
        };  // class Container



        class OBBEXPDLL Container_out
         {
            public:
                Container_out (Container_ptr & p);
                Container_out (Container_var & p);
                Container_out (const Container_out & p) : ptr_(p.ptr_) {}
                Container_out & operator=(const Container_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Container_out & operator=(const Container_var & a);
                Container_out & operator=(Container_ptr p) {
                ptr_ = p; return *this;}
                inline operator Container_ptr & () { return ptr_; }
                inline Container_ptr & ptr () { return ptr_; }
                inline Container_ptr operator->() { return ptr_; }
            private:
                Container_ptr & ptr_;
        };  // class Container_out



        static const TypeCode_ptr _tc_IDLType;
        class OBBEXPDLL IDLType : public virtual  IRObject
         {
            public:
                static IDLType_ptr _duplicate(IDLType_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static IDLType_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static IDLType_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual TypeCode_ptr type (); 

            protected:
                IDLType(Object_ptr obj = 0);
                virtual ~IDLType(){ }

            private:
                IDLType( const IDLType&) { }
                void operator=(const IDLType&) { }
                ORB_ptr pORB;
        };  // class IDLType



        class OBBEXPDLL IDLType_out
         {
            public:
                IDLType_out (IDLType_ptr & p);
                IDLType_out (IDLType_var & p);
                IDLType_out (const IDLType_out & p) : ptr_(p.ptr_) {}
                IDLType_out & operator=(const IDLType_out & a) {
                    ptr_ = a.ptr_; return *this;}
                IDLType_out & operator=(const IDLType_var & a);
                IDLType_out & operator=(IDLType_ptr p) {
                ptr_ = p; return *this;}
                inline operator IDLType_ptr & () { return ptr_; }
                inline IDLType_ptr & ptr () { return ptr_; }
                inline IDLType_ptr operator->() { return ptr_; }
            private:
                IDLType_ptr & ptr_;
        };  // class IDLType_out



        enum PrimitiveKind { pk_null, pk_void, pk_short, pk_long, pk_ushort, pk_ulong, pk_float, pk_double, pk_boolean, pk_char, pk_octet, pk_any, pk_TypeCode, pk_Principal, pk_string, pk_objref, pk_longlong, pk_ulonglong, pk_longdouble, pk_wchar, pk_wstring, pk_value_base };
        typedef PrimitiveKind & PrimitiveKind_out ;
        static const TypeCode_ptr _tc_PrimitiveKind;


        static const TypeCode_ptr _tc_Repository;
        class OBBEXPDLL Repository : public virtual  Container
         {
            public:
                static Repository_ptr _duplicate(Repository_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Repository_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static Repository_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Contained_ptr lookup_id (
                    const char * search_id); 

                virtual TypeCode_ptr get_canonical_typecode (
                    TypeCode_ptr tc); 

                virtual PrimitiveDef_ptr get_primitive (
                    PrimitiveKind kind); 

                virtual StringDef_ptr create_string (
                    ULong bound); 

                virtual WstringDef_ptr create_wstring (
                    ULong bound); 

                virtual SequenceDef_ptr create_sequence (
                    ULong bound,
                    IDLType_ptr element_type); 

                virtual ArrayDef_ptr create_array (
                    ULong length,
                    IDLType_ptr element_type); 

                virtual FixedDef_ptr create_fixed (
                    UShort digits,
                    Short scale); 

            protected:
                Repository(Object_ptr obj = 0);
                virtual ~Repository(){ }

            private:
                Repository( const Repository&) { }
                void operator=(const Repository&) { }
                ORB_ptr pORB;
        };  // class Repository



        class OBBEXPDLL Repository_out
         {
            public:
                Repository_out (Repository_ptr & p);
                Repository_out (Repository_var & p);
                Repository_out (const Repository_out & p) : ptr_(p.ptr_) {}
                Repository_out & operator=(const Repository_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Repository_out & operator=(const Repository_var & a);
                Repository_out & operator=(Repository_ptr p) {
                ptr_ = p; return *this;}
                inline operator Repository_ptr & () { return ptr_; }
                inline Repository_ptr & ptr () { return ptr_; }
                inline Repository_ptr operator->() { return ptr_; }
            private:
                Repository_ptr & ptr_;
        };  // class Repository_out



        static const TypeCode_ptr _tc_ModuleDef;
        class OBBEXPDLL ModuleDef : public virtual  Container, public virtual  Contained
         {
            public:
                static ModuleDef_ptr _duplicate(ModuleDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static ModuleDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static ModuleDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

            protected:
                ModuleDef(Object_ptr obj = 0);
                virtual ~ModuleDef(){ }

            private:
                ModuleDef( const ModuleDef&) { }
                void operator=(const ModuleDef&) { }
                ORB_ptr pORB;
        };  // class ModuleDef



        class OBBEXPDLL ModuleDef_out
         {
            public:
                ModuleDef_out (ModuleDef_ptr & p);
                ModuleDef_out (ModuleDef_var & p);
                ModuleDef_out (const ModuleDef_out & p) : ptr_(p.ptr_) {}
                ModuleDef_out & operator=(const ModuleDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                ModuleDef_out & operator=(const ModuleDef_var & a);
                ModuleDef_out & operator=(ModuleDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator ModuleDef_ptr & () { return ptr_; }
                inline ModuleDef_ptr & ptr () { return ptr_; }
                inline ModuleDef_ptr operator->() { return ptr_; }
            private:
                ModuleDef_ptr & ptr_;
        };  // class ModuleDef_out



        struct OBBEXPDLL ModuleDescription {
            String_var name;
            String_var id;
            String_var defined_in;
            String_var version;
            ModuleDescription &operator=(const ModuleDescription &_obj);
        };
        typedef	ModuleDescription *	ModuleDescription_ptr;
        class OBBEXPDLL ModuleDescription_var
        {
            public:
                inline ModuleDescription_var() {_ptr = 0;}
                inline ModuleDescription_var(ModuleDescription *_obj) {_ptr = _obj;}
                ModuleDescription_var(const ModuleDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~ModuleDescription_var();
                ModuleDescription_var &operator=(ModuleDescription *);
                ModuleDescription_var &operator=(const ModuleDescription_var &);
                inline ModuleDescription *operator->() {return _ptr;}
                inline const ModuleDescription *operator->() const {return _ptr;}
                inline const ModuleDescription & in () const { return *_ptr; }
                inline ModuleDescription & inout () { return *_ptr; }
                ModuleDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ModuleDescription * _retn ()
                {
                    ModuleDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ModuleDescription_ptr & ptr() { return _ptr; }
                inline operator ModuleDescription&() { return *_ptr; }
                inline operator const ModuleDescription&() const { return *_ptr; }
                inline operator ModuleDescription_ptr &() { return _ptr; }
            private:
                ModuleDescription *_ptr;
        };  // class ModuleDescription_var

        class OBBEXPDLL ModuleDescription_out
        {
            public:
                ModuleDescription_out (ModuleDescription *& p) : ptr_(p) { ptr_ = 0; }
                ModuleDescription_out (ModuleDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ModuleDescription_out (const ModuleDescription_out & a) : ptr_(a.ptr_) {}
                ModuleDescription_out & operator=(const ModuleDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ModuleDescription_out & operator=(ModuleDescription * p) {
                    ptr_ = p; return *this; }
                inline operator ModuleDescription_ptr & () { return ptr_; }
                inline ModuleDescription_ptr & ptr () { return ptr_; }
                inline ModuleDescription_ptr operator->() { return ptr_; }
            private:
                ModuleDescription_ptr & ptr_;
                void operator=(const ModuleDescription_var &);

        };  // class ModuleDescription_out
        static const TypeCode_ptr _tc_ModuleDescription;


        static const TypeCode_ptr _tc_ConstantDef;
        class OBBEXPDLL ConstantDef : public virtual  Contained
         {
            public:
                static ConstantDef_ptr _duplicate(ConstantDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static ConstantDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static ConstantDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual TypeCode_ptr type (); 

                virtual IDLType_ptr type_def (); 

                virtual void type_def (
                    IDLType_ptr type_def); 

                virtual Any * value (); 

                virtual void value (
                     const Any & value); 

            protected:
                ConstantDef(Object_ptr obj = 0);
                virtual ~ConstantDef(){ }

            private:
                ConstantDef( const ConstantDef&) { }
                void operator=(const ConstantDef&) { }
                ORB_ptr pORB;
        };  // class ConstantDef



        class OBBEXPDLL ConstantDef_out
         {
            public:
                ConstantDef_out (ConstantDef_ptr & p);
                ConstantDef_out (ConstantDef_var & p);
                ConstantDef_out (const ConstantDef_out & p) : ptr_(p.ptr_) {}
                ConstantDef_out & operator=(const ConstantDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                ConstantDef_out & operator=(const ConstantDef_var & a);
                ConstantDef_out & operator=(ConstantDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator ConstantDef_ptr & () { return ptr_; }
                inline ConstantDef_ptr & ptr () { return ptr_; }
                inline ConstantDef_ptr operator->() { return ptr_; }
            private:
                ConstantDef_ptr & ptr_;
        };  // class ConstantDef_out



        struct OBBEXPDLL ConstantDescription {
            String_var name;
            String_var id;
            String_var defined_in;
            String_var version;


             TypeCode_var type;
             Any value;
            ConstantDescription &operator=(const ConstantDescription &_obj);
        };
        typedef	ConstantDescription *	ConstantDescription_ptr;
        class OBBEXPDLL ConstantDescription_var
        {
            public:
                inline ConstantDescription_var() {_ptr = 0;}
                inline ConstantDescription_var(ConstantDescription *_obj) {_ptr = _obj;}
                ConstantDescription_var(const ConstantDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~ConstantDescription_var();
                ConstantDescription_var &operator=(ConstantDescription *);
                ConstantDescription_var &operator=(const ConstantDescription_var &);
                inline ConstantDescription *operator->() {return _ptr;}
                inline const ConstantDescription *operator->() const {return _ptr;}
                inline const ConstantDescription & in () const { return *_ptr; }
                inline ConstantDescription & inout () { return *_ptr; }
                ConstantDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ConstantDescription * _retn ()
                {
                    ConstantDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ConstantDescription_ptr & ptr() { return _ptr; }
                inline operator ConstantDescription&() { return *_ptr; }
                inline operator const ConstantDescription&() const { return *_ptr; }
                inline operator ConstantDescription_ptr &() { return _ptr; }
            private:
                ConstantDescription *_ptr;
        };  // class ConstantDescription_var

        class OBBEXPDLL ConstantDescription_out
        {
            public:
                ConstantDescription_out (ConstantDescription *& p) : ptr_(p) { ptr_ = 0; }
                ConstantDescription_out (ConstantDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ConstantDescription_out (const ConstantDescription_out & a) : ptr_(a.ptr_) {}
                ConstantDescription_out & operator=(const ConstantDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ConstantDescription_out & operator=(ConstantDescription * p) {
                    ptr_ = p; return *this; }
                inline operator ConstantDescription_ptr & () { return ptr_; }
                inline ConstantDescription_ptr & ptr () { return ptr_; }
                inline ConstantDescription_ptr operator->() { return ptr_; }
            private:
                ConstantDescription_ptr & ptr_;
                void operator=(const ConstantDescription_var &);

        };  // class ConstantDescription_out
        static const TypeCode_ptr _tc_ConstantDescription;


        static const TypeCode_ptr _tc_TypedefDef;
        class OBBEXPDLL TypedefDef : public virtual  Contained, public virtual  IDLType
         {
            public:
                static TypedefDef_ptr _duplicate(TypedefDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static TypedefDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static TypedefDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

            protected:
                TypedefDef(Object_ptr obj = 0);
                virtual ~TypedefDef(){ }

            private:
                TypedefDef( const TypedefDef&) { }
                void operator=(const TypedefDef&) { }
                ORB_ptr pORB;
        };  // class TypedefDef



        class OBBEXPDLL TypedefDef_out
         {
            public:
                TypedefDef_out (TypedefDef_ptr & p);
                TypedefDef_out (TypedefDef_var & p);
                TypedefDef_out (const TypedefDef_out & p) : ptr_(p.ptr_) {}
                TypedefDef_out & operator=(const TypedefDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                TypedefDef_out & operator=(const TypedefDef_var & a);
                TypedefDef_out & operator=(TypedefDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator TypedefDef_ptr & () { return ptr_; }
                inline TypedefDef_ptr & ptr () { return ptr_; }
                inline TypedefDef_ptr operator->() { return ptr_; }
            private:
                TypedefDef_ptr & ptr_;
        };  // class TypedefDef_out



        struct OBBEXPDLL TypeDescription {
            String_var name;
            String_var id;
            String_var defined_in;
            String_var version;


             TypeCode_var type;
            TypeDescription &operator=(const TypeDescription &_obj);
        };
        typedef	TypeDescription *	TypeDescription_ptr;
        class OBBEXPDLL TypeDescription_var
        {
            public:
                inline TypeDescription_var() {_ptr = 0;}
                inline TypeDescription_var(TypeDescription *_obj) {_ptr = _obj;}
                TypeDescription_var(const TypeDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~TypeDescription_var();
                TypeDescription_var &operator=(TypeDescription *);
                TypeDescription_var &operator=(const TypeDescription_var &);
                inline TypeDescription *operator->() {return _ptr;}
                inline const TypeDescription *operator->() const {return _ptr;}
                inline const TypeDescription & in () const { return *_ptr; }
                inline TypeDescription & inout () { return *_ptr; }
                TypeDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                TypeDescription * _retn ()
                {
                    TypeDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline TypeDescription_ptr & ptr() { return _ptr; }
                inline operator TypeDescription&() { return *_ptr; }
                inline operator const TypeDescription&() const { return *_ptr; }
                inline operator TypeDescription_ptr &() { return _ptr; }
            private:
                TypeDescription *_ptr;
        };  // class TypeDescription_var

        class OBBEXPDLL TypeDescription_out
        {
            public:
                TypeDescription_out (TypeDescription *& p) : ptr_(p) { ptr_ = 0; }
                TypeDescription_out (TypeDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                TypeDescription_out (const TypeDescription_out & a) : ptr_(a.ptr_) {}
                TypeDescription_out & operator=(const TypeDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                TypeDescription_out & operator=(TypeDescription * p) {
                    ptr_ = p; return *this; }
                inline operator TypeDescription_ptr & () { return ptr_; }
                inline TypeDescription_ptr & ptr () { return ptr_; }
                inline TypeDescription_ptr operator->() { return ptr_; }
            private:
                TypeDescription_ptr & ptr_;
                void operator=(const TypeDescription_var &);

        };  // class TypeDescription_out
        static const TypeCode_ptr _tc_TypeDescription;


        static const TypeCode_ptr _tc_StructDef;
        class OBBEXPDLL StructDef : public virtual  TypedefDef
         {
            public:
                static StructDef_ptr _duplicate(StructDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static StructDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static StructDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual StructMemberSeq * members (); 

                virtual void members (
                     const StructMemberSeq & members); 

            protected:
                StructDef(Object_ptr obj = 0);
                virtual ~StructDef(){ }

            private:
                StructDef( const StructDef&) { }
                void operator=(const StructDef&) { }
                ORB_ptr pORB;
        };  // class StructDef



        class OBBEXPDLL StructDef_out
         {
            public:
                StructDef_out (StructDef_ptr & p);
                StructDef_out (StructDef_var & p);
                StructDef_out (const StructDef_out & p) : ptr_(p.ptr_) {}
                StructDef_out & operator=(const StructDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                StructDef_out & operator=(const StructDef_var & a);
                StructDef_out & operator=(StructDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator StructDef_ptr & () { return ptr_; }
                inline StructDef_ptr & ptr () { return ptr_; }
                inline StructDef_ptr operator->() { return ptr_; }
            private:
                StructDef_ptr & ptr_;
        };  // class StructDef_out



        static const TypeCode_ptr _tc_UnionDef;
        class OBBEXPDLL UnionDef : public virtual  TypedefDef, public virtual  Container
         {
            public:
                static UnionDef_ptr _duplicate(UnionDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static UnionDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static UnionDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual TypeCode_ptr discriminator_type (); 

                virtual IDLType_ptr discriminator_type_def (); 

                virtual void discriminator_type_def (
                    IDLType_ptr discriminator_type_def); 

                virtual UnionMemberSeq * members (); 

                virtual void members (
                     const UnionMemberSeq & members); 

            protected:
                UnionDef(Object_ptr obj = 0);
                virtual ~UnionDef(){ }

            private:
                UnionDef( const UnionDef&) { }
                void operator=(const UnionDef&) { }
                ORB_ptr pORB;
        };  // class UnionDef



        class OBBEXPDLL UnionDef_out
         {
            public:
                UnionDef_out (UnionDef_ptr & p);
                UnionDef_out (UnionDef_var & p);
                UnionDef_out (const UnionDef_out & p) : ptr_(p.ptr_) {}
                UnionDef_out & operator=(const UnionDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                UnionDef_out & operator=(const UnionDef_var & a);
                UnionDef_out & operator=(UnionDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator UnionDef_ptr & () { return ptr_; }
                inline UnionDef_ptr & ptr () { return ptr_; }
                inline UnionDef_ptr operator->() { return ptr_; }
            private:
                UnionDef_ptr & ptr_;
        };  // class UnionDef_out



        static const TypeCode_ptr _tc_EnumDef;
        class OBBEXPDLL EnumDef : public virtual  TypedefDef
         {
            public:
                static EnumDef_ptr _duplicate(EnumDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static EnumDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static EnumDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual EnumMemberSeq * members (); 

                virtual void members (
                     const EnumMemberSeq & members); 

            protected:
                EnumDef(Object_ptr obj = 0);
                virtual ~EnumDef(){ }

            private:
                EnumDef( const EnumDef&) { }
                void operator=(const EnumDef&) { }
                ORB_ptr pORB;
        };  // class EnumDef



        class OBBEXPDLL EnumDef_out
         {
            public:
                EnumDef_out (EnumDef_ptr & p);
                EnumDef_out (EnumDef_var & p);
                EnumDef_out (const EnumDef_out & p) : ptr_(p.ptr_) {}
                EnumDef_out & operator=(const EnumDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                EnumDef_out & operator=(const EnumDef_var & a);
                EnumDef_out & operator=(EnumDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator EnumDef_ptr & () { return ptr_; }
                inline EnumDef_ptr & ptr () { return ptr_; }
                inline EnumDef_ptr operator->() { return ptr_; }
            private:
                EnumDef_ptr & ptr_;
        };  // class EnumDef_out



        static const TypeCode_ptr _tc_AliasDef;
        class OBBEXPDLL AliasDef : public virtual  TypedefDef
         {
            public:
                static AliasDef_ptr _duplicate(AliasDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static AliasDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static AliasDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual IDLType_ptr original_type_def (); 

                virtual void original_type_def (
                    IDLType_ptr original_type_def); 

            protected:
                AliasDef(Object_ptr obj = 0);
                virtual ~AliasDef(){ }

            private:
                AliasDef( const AliasDef&) { }
                void operator=(const AliasDef&) { }
                ORB_ptr pORB;
        };  // class AliasDef



        class OBBEXPDLL AliasDef_out
         {
            public:
                AliasDef_out (AliasDef_ptr & p);
                AliasDef_out (AliasDef_var & p);
                AliasDef_out (const AliasDef_out & p) : ptr_(p.ptr_) {}
                AliasDef_out & operator=(const AliasDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                AliasDef_out & operator=(const AliasDef_var & a);
                AliasDef_out & operator=(AliasDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator AliasDef_ptr & () { return ptr_; }
                inline AliasDef_ptr & ptr () { return ptr_; }
                inline AliasDef_ptr operator->() { return ptr_; }
            private:
                AliasDef_ptr & ptr_;
        };  // class AliasDef_out



        static const TypeCode_ptr _tc_NativeDef;
        class OBBEXPDLL NativeDef : public virtual  TypedefDef
         {
            public:
                static NativeDef_ptr _duplicate(NativeDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static NativeDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static NativeDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

            protected:
                NativeDef(Object_ptr obj = 0);
                virtual ~NativeDef(){ }

            private:
                NativeDef( const NativeDef&) { }
                void operator=(const NativeDef&) { }
                ORB_ptr pORB;
        };  // class NativeDef



        class OBBEXPDLL NativeDef_out
         {
            public:
                NativeDef_out (NativeDef_ptr & p);
                NativeDef_out (NativeDef_var & p);
                NativeDef_out (const NativeDef_out & p) : ptr_(p.ptr_) {}
                NativeDef_out & operator=(const NativeDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                NativeDef_out & operator=(const NativeDef_var & a);
                NativeDef_out & operator=(NativeDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator NativeDef_ptr & () { return ptr_; }
                inline NativeDef_ptr & ptr () { return ptr_; }
                inline NativeDef_ptr operator->() { return ptr_; }
            private:
                NativeDef_ptr & ptr_;
        };  // class NativeDef_out



        static const TypeCode_ptr _tc_PrimitiveDef;
        class OBBEXPDLL PrimitiveDef : public virtual  IDLType
         {
            public:
                static PrimitiveDef_ptr _duplicate(PrimitiveDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static PrimitiveDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static PrimitiveDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual PrimitiveKind kind (); 

            protected:
                PrimitiveDef(Object_ptr obj = 0);
                virtual ~PrimitiveDef(){ }

            private:
                PrimitiveDef( const PrimitiveDef&) { }
                void operator=(const PrimitiveDef&) { }
                ORB_ptr pORB;
        };  // class PrimitiveDef



        class OBBEXPDLL PrimitiveDef_out
         {
            public:
                PrimitiveDef_out (PrimitiveDef_ptr & p);
                PrimitiveDef_out (PrimitiveDef_var & p);
                PrimitiveDef_out (const PrimitiveDef_out & p) : ptr_(p.ptr_) {}
                PrimitiveDef_out & operator=(const PrimitiveDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                PrimitiveDef_out & operator=(const PrimitiveDef_var & a);
                PrimitiveDef_out & operator=(PrimitiveDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator PrimitiveDef_ptr & () { return ptr_; }
                inline PrimitiveDef_ptr & ptr () { return ptr_; }
                inline PrimitiveDef_ptr operator->() { return ptr_; }
            private:
                PrimitiveDef_ptr & ptr_;
        };  // class PrimitiveDef_out



        static const TypeCode_ptr _tc_StringDef;
        class OBBEXPDLL StringDef : public virtual  IDLType
         {
            public:
                static StringDef_ptr _duplicate(StringDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static StringDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static StringDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual ULong bound (); 

                virtual void bound (
                    ULong bound); 

            protected:
                StringDef(Object_ptr obj = 0);
                virtual ~StringDef(){ }

            private:
                StringDef( const StringDef&) { }
                void operator=(const StringDef&) { }
                ORB_ptr pORB;
        };  // class StringDef



        class OBBEXPDLL StringDef_out
         {
            public:
                StringDef_out (StringDef_ptr & p);
                StringDef_out (StringDef_var & p);
                StringDef_out (const StringDef_out & p) : ptr_(p.ptr_) {}
                StringDef_out & operator=(const StringDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                StringDef_out & operator=(const StringDef_var & a);
                StringDef_out & operator=(StringDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator StringDef_ptr & () { return ptr_; }
                inline StringDef_ptr & ptr () { return ptr_; }
                inline StringDef_ptr operator->() { return ptr_; }
            private:
                StringDef_ptr & ptr_;
        };  // class StringDef_out



        static const TypeCode_ptr _tc_WstringDef;
        class OBBEXPDLL WstringDef : public virtual  IDLType
         {
            public:
                static WstringDef_ptr _duplicate(WstringDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static WstringDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static WstringDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual ULong bound (); 

                virtual void bound (
                    ULong bound); 

            protected:
                WstringDef(Object_ptr obj = 0);
                virtual ~WstringDef(){ }

            private:
                WstringDef( const WstringDef&) { }
                void operator=(const WstringDef&) { }
                ORB_ptr pORB;
        };  // class WstringDef



        class OBBEXPDLL WstringDef_out
         {
            public:
                WstringDef_out (WstringDef_ptr & p);
                WstringDef_out (WstringDef_var & p);
                WstringDef_out (const WstringDef_out & p) : ptr_(p.ptr_) {}
                WstringDef_out & operator=(const WstringDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                WstringDef_out & operator=(const WstringDef_var & a);
                WstringDef_out & operator=(WstringDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator WstringDef_ptr & () { return ptr_; }
                inline WstringDef_ptr & ptr () { return ptr_; }
                inline WstringDef_ptr operator->() { return ptr_; }
            private:
                WstringDef_ptr & ptr_;
        };  // class WstringDef_out



        static const TypeCode_ptr _tc_FixedDef;
        class OBBEXPDLL FixedDef : public virtual  IDLType
         {
            public:
                static FixedDef_ptr _duplicate(FixedDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static FixedDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static FixedDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual UShort digits (); 

                virtual void digits (
                    UShort digits); 

                virtual Short scale (); 

                virtual void scale (
                    Short scale); 

            protected:
                FixedDef(Object_ptr obj = 0);
                virtual ~FixedDef(){ }

            private:
                FixedDef( const FixedDef&) { }
                void operator=(const FixedDef&) { }
                ORB_ptr pORB;
        };  // class FixedDef



        class OBBEXPDLL FixedDef_out
         {
            public:
                FixedDef_out (FixedDef_ptr & p);
                FixedDef_out (FixedDef_var & p);
                FixedDef_out (const FixedDef_out & p) : ptr_(p.ptr_) {}
                FixedDef_out & operator=(const FixedDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                FixedDef_out & operator=(const FixedDef_var & a);
                FixedDef_out & operator=(FixedDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator FixedDef_ptr & () { return ptr_; }
                inline FixedDef_ptr & ptr () { return ptr_; }
                inline FixedDef_ptr operator->() { return ptr_; }
            private:
                FixedDef_ptr & ptr_;
        };  // class FixedDef_out



        static const TypeCode_ptr _tc_SequenceDef;
        class OBBEXPDLL SequenceDef : public virtual  IDLType
         {
            public:
                static SequenceDef_ptr _duplicate(SequenceDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static SequenceDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static SequenceDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual ULong bound (); 

                virtual void bound (
                    ULong bound); 

                virtual TypeCode_ptr element_type (); 

                virtual IDLType_ptr element_type_def (); 

                virtual void element_type_def (
                    IDLType_ptr element_type_def); 

            protected:
                SequenceDef(Object_ptr obj = 0);
                virtual ~SequenceDef(){ }

            private:
                SequenceDef( const SequenceDef&) { }
                void operator=(const SequenceDef&) { }
                ORB_ptr pORB;
        };  // class SequenceDef



        class OBBEXPDLL SequenceDef_out
         {
            public:
                SequenceDef_out (SequenceDef_ptr & p);
                SequenceDef_out (SequenceDef_var & p);
                SequenceDef_out (const SequenceDef_out & p) : ptr_(p.ptr_) {}
                SequenceDef_out & operator=(const SequenceDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                SequenceDef_out & operator=(const SequenceDef_var & a);
                SequenceDef_out & operator=(SequenceDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator SequenceDef_ptr & () { return ptr_; }
                inline SequenceDef_ptr & ptr () { return ptr_; }
                inline SequenceDef_ptr operator->() { return ptr_; }
            private:
                SequenceDef_ptr & ptr_;
        };  // class SequenceDef_out



        static const TypeCode_ptr _tc_ArrayDef;
        class OBBEXPDLL ArrayDef : public virtual  IDLType
         {
            public:
                static ArrayDef_ptr _duplicate(ArrayDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static ArrayDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static ArrayDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual ULong length (); 

                virtual void length (
                    ULong length); 

                virtual TypeCode_ptr element_type (); 

                virtual IDLType_ptr element_type_def (); 

                virtual void element_type_def (
                    IDLType_ptr element_type_def); 

            protected:
                ArrayDef(Object_ptr obj = 0);
                virtual ~ArrayDef(){ }

            private:
                ArrayDef( const ArrayDef&) { }
                void operator=(const ArrayDef&) { }
                ORB_ptr pORB;
        };  // class ArrayDef



        class OBBEXPDLL ArrayDef_out
         {
            public:
                ArrayDef_out (ArrayDef_ptr & p);
                ArrayDef_out (ArrayDef_var & p);
                ArrayDef_out (const ArrayDef_out & p) : ptr_(p.ptr_) {}
                ArrayDef_out & operator=(const ArrayDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                ArrayDef_out & operator=(const ArrayDef_var & a);
                ArrayDef_out & operator=(ArrayDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator ArrayDef_ptr & () { return ptr_; }
                inline ArrayDef_ptr & ptr () { return ptr_; }
                inline ArrayDef_ptr operator->() { return ptr_; }
            private:
                ArrayDef_ptr & ptr_;
        };  // class ArrayDef_out



        static const TypeCode_ptr _tc_ExceptionDef;
        class OBBEXPDLL ExceptionDef : public virtual  Contained, public virtual  Container
         {
            public:
                static ExceptionDef_ptr _duplicate(ExceptionDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static ExceptionDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static ExceptionDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual TypeCode_ptr type (); 

                virtual StructMemberSeq * members (); 

                virtual void members (
                     const StructMemberSeq & members); 

            protected:
                ExceptionDef(Object_ptr obj = 0);
                virtual ~ExceptionDef(){ }

            private:
                ExceptionDef( const ExceptionDef&) { }
                void operator=(const ExceptionDef&) { }
                ORB_ptr pORB;
        };  // class ExceptionDef



        class OBBEXPDLL ExceptionDef_out
         {
            public:
                ExceptionDef_out (ExceptionDef_ptr & p);
                ExceptionDef_out (ExceptionDef_var & p);
                ExceptionDef_out (const ExceptionDef_out & p) : ptr_(p.ptr_) {}
                ExceptionDef_out & operator=(const ExceptionDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                ExceptionDef_out & operator=(const ExceptionDef_var & a);
                ExceptionDef_out & operator=(ExceptionDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator ExceptionDef_ptr & () { return ptr_; }
                inline ExceptionDef_ptr & ptr () { return ptr_; }
                inline ExceptionDef_ptr operator->() { return ptr_; }
            private:
                ExceptionDef_ptr & ptr_;
        };  // class ExceptionDef_out



        struct OBBEXPDLL ExceptionDescription {
            String_var name;
            String_var id;
            String_var defined_in;
            String_var version;


             TypeCode_var type;
            ExceptionDescription &operator=(const ExceptionDescription &_obj);
        };
        typedef	ExceptionDescription *	ExceptionDescription_ptr;
        class OBBEXPDLL ExceptionDescription_var
        {
            public:
                inline ExceptionDescription_var() {_ptr = 0;}
                inline ExceptionDescription_var(ExceptionDescription *_obj) {_ptr = _obj;}
                ExceptionDescription_var(const ExceptionDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~ExceptionDescription_var();
                ExceptionDescription_var &operator=(ExceptionDescription *);
                ExceptionDescription_var &operator=(const ExceptionDescription_var &);
                inline ExceptionDescription *operator->() {return _ptr;}
                inline const ExceptionDescription *operator->() const {return _ptr;}
                inline const ExceptionDescription & in () const { return *_ptr; }
                inline ExceptionDescription & inout () { return *_ptr; }
                ExceptionDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ExceptionDescription * _retn ()
                {
                    ExceptionDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ExceptionDescription_ptr & ptr() { return _ptr; }
                inline operator ExceptionDescription&() { return *_ptr; }
                inline operator const ExceptionDescription&() const { return *_ptr; }
                inline operator ExceptionDescription_ptr &() { return _ptr; }
            private:
                ExceptionDescription *_ptr;
        };  // class ExceptionDescription_var

        class OBBEXPDLL ExceptionDescription_out
        {
            public:
                ExceptionDescription_out (ExceptionDescription *& p) : ptr_(p) { ptr_ = 0; }
                ExceptionDescription_out (ExceptionDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ExceptionDescription_out (const ExceptionDescription_out & a) : ptr_(a.ptr_) {}
                ExceptionDescription_out & operator=(const ExceptionDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ExceptionDescription_out & operator=(ExceptionDescription * p) {
                    ptr_ = p; return *this; }
                inline operator ExceptionDescription_ptr & () { return ptr_; }
                inline ExceptionDescription_ptr & ptr () { return ptr_; }
                inline ExceptionDescription_ptr operator->() { return ptr_; }
            private:
                ExceptionDescription_ptr & ptr_;
                void operator=(const ExceptionDescription_var &);

        };  // class ExceptionDescription_out
        static const TypeCode_ptr _tc_ExceptionDescription;


        enum AttributeMode { ATTR_NORMAL, ATTR_READONLY };
        typedef AttributeMode & AttributeMode_out ;
        static const TypeCode_ptr _tc_AttributeMode;


        static const TypeCode_ptr _tc_AttributeDef;
        class OBBEXPDLL AttributeDef : public virtual  Contained
         {
            public:
                static AttributeDef_ptr _duplicate(AttributeDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static AttributeDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static AttributeDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual TypeCode_ptr type (); 

                virtual IDLType_ptr type_def (); 

                virtual void type_def (
                    IDLType_ptr type_def); 

                virtual AttributeMode mode (); 

                virtual void mode (
                    AttributeMode mode); 

            protected:
                AttributeDef(Object_ptr obj = 0);
                virtual ~AttributeDef(){ }

            private:
                AttributeDef( const AttributeDef&) { }
                void operator=(const AttributeDef&) { }
                ORB_ptr pORB;
        };  // class AttributeDef



        class OBBEXPDLL AttributeDef_out
         {
            public:
                AttributeDef_out (AttributeDef_ptr & p);
                AttributeDef_out (AttributeDef_var & p);
                AttributeDef_out (const AttributeDef_out & p) : ptr_(p.ptr_) {}
                AttributeDef_out & operator=(const AttributeDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                AttributeDef_out & operator=(const AttributeDef_var & a);
                AttributeDef_out & operator=(AttributeDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator AttributeDef_ptr & () { return ptr_; }
                inline AttributeDef_ptr & ptr () { return ptr_; }
                inline AttributeDef_ptr operator->() { return ptr_; }
            private:
                AttributeDef_ptr & ptr_;
        };  // class AttributeDef_out



        struct OBBEXPDLL AttributeDescription {
            String_var name;
            String_var id;
            String_var defined_in;
            String_var version;


             TypeCode_var type;


             AttributeMode mode;
            AttributeDescription &operator=(const AttributeDescription &_obj);
        };
        typedef	AttributeDescription *	AttributeDescription_ptr;
        class OBBEXPDLL AttributeDescription_var
        {
            public:
                inline AttributeDescription_var() {_ptr = 0;}
                inline AttributeDescription_var(AttributeDescription *_obj) {_ptr = _obj;}
                AttributeDescription_var(const AttributeDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~AttributeDescription_var();
                AttributeDescription_var &operator=(AttributeDescription *);
                AttributeDescription_var &operator=(const AttributeDescription_var &);
                inline AttributeDescription *operator->() {return _ptr;}
                inline const AttributeDescription *operator->() const {return _ptr;}
                inline const AttributeDescription & in () const { return *_ptr; }
                inline AttributeDescription & inout () { return *_ptr; }
                AttributeDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                AttributeDescription * _retn ()
                {
                    AttributeDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline AttributeDescription_ptr & ptr() { return _ptr; }
                inline operator AttributeDescription&() { return *_ptr; }
                inline operator const AttributeDescription&() const { return *_ptr; }
                inline operator AttributeDescription_ptr &() { return _ptr; }
            private:
                AttributeDescription *_ptr;
        };  // class AttributeDescription_var

        class OBBEXPDLL AttributeDescription_out
        {
            public:
                AttributeDescription_out (AttributeDescription *& p) : ptr_(p) { ptr_ = 0; }
                AttributeDescription_out (AttributeDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                AttributeDescription_out (const AttributeDescription_out & a) : ptr_(a.ptr_) {}
                AttributeDescription_out & operator=(const AttributeDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                AttributeDescription_out & operator=(AttributeDescription * p) {
                    ptr_ = p; return *this; }
                inline operator AttributeDescription_ptr & () { return ptr_; }
                inline AttributeDescription_ptr & ptr () { return ptr_; }
                inline AttributeDescription_ptr operator->() { return ptr_; }
            private:
                AttributeDescription_ptr & ptr_;
                void operator=(const AttributeDescription_var &);

        };  // class AttributeDescription_out
        static const TypeCode_ptr _tc_AttributeDescription;


        enum OperationMode { OP_NORMAL, OP_ONEWAY };
        typedef OperationMode & OperationMode_out ;
        static const TypeCode_ptr _tc_OperationMode;


        enum ParameterMode { PARAM_IN, PARAM_OUT, PARAM_INOUT };
        typedef ParameterMode & ParameterMode_out ;
        static const TypeCode_ptr _tc_ParameterMode;


        struct OBBEXPDLL ParameterDescription {
            String_var name;


             TypeCode_var type;


             IDLType_var type_def;


             ParameterMode mode;
            ParameterDescription &operator=(const ParameterDescription &_obj);
        };
        typedef	ParameterDescription *	ParameterDescription_ptr;
        class OBBEXPDLL ParameterDescription_var
        {
            public:
                inline ParameterDescription_var() {_ptr = 0;}
                inline ParameterDescription_var(ParameterDescription *_obj) {_ptr = _obj;}
                ParameterDescription_var(const ParameterDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~ParameterDescription_var();
                ParameterDescription_var &operator=(ParameterDescription *);
                ParameterDescription_var &operator=(const ParameterDescription_var &);
                inline ParameterDescription *operator->() {return _ptr;}
                inline const ParameterDescription *operator->() const {return _ptr;}
                inline const ParameterDescription & in () const { return *_ptr; }
                inline ParameterDescription & inout () { return *_ptr; }
                ParameterDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ParameterDescription * _retn ()
                {
                    ParameterDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ParameterDescription_ptr & ptr() { return _ptr; }
                inline operator ParameterDescription&() { return *_ptr; }
                inline operator const ParameterDescription&() const { return *_ptr; }
                inline operator ParameterDescription_ptr &() { return _ptr; }
            private:
                ParameterDescription *_ptr;
        };  // class ParameterDescription_var

        class OBBEXPDLL ParameterDescription_out
        {
            public:
                ParameterDescription_out (ParameterDescription *& p) : ptr_(p) { ptr_ = 0; }
                ParameterDescription_out (ParameterDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ParameterDescription_out (const ParameterDescription_out & a) : ptr_(a.ptr_) {}
                ParameterDescription_out & operator=(const ParameterDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ParameterDescription_out & operator=(ParameterDescription * p) {
                    ptr_ = p; return *this; }
                inline operator ParameterDescription_ptr & () { return ptr_; }
                inline ParameterDescription_ptr & ptr () { return ptr_; }
                inline ParameterDescription_ptr operator->() { return ptr_; }
            private:
                ParameterDescription_ptr & ptr_;
                void operator=(const ParameterDescription_var &);

        };  // class ParameterDescription_out
        static const TypeCode_ptr _tc_ParameterDescription;


        class OBBEXPDLL ParDescriptionSeq
        {
            public:
                ParDescriptionSeq();

                ParDescriptionSeq(ULong _max);

                ParDescriptionSeq
                (
                    ULong _max,
                    ULong _length,
                    ParameterDescription *_value,
                    Boolean _relse = CORBA_FALSE
                );

                ParDescriptionSeq(const ParDescriptionSeq &_ptr);

                ~ParDescriptionSeq();

                ParDescriptionSeq &operator=(const ParDescriptionSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline ParameterDescription &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const ParameterDescription &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const ParameterDescription &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static ParameterDescription *allocbuf(ULong _nelems);
                static void freebuf(ParameterDescription *_ptr);

                inline ParameterDescription * OBB__GetData() { return _data; }
            private:
                ParameterDescription *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class ParDescriptionSeq

        typedef	ParDescriptionSeq *	ParDescriptionSeq_ptr;
        class OBBEXPDLL ParDescriptionSeq_var
        {
            public:
                inline ParDescriptionSeq_var() {_ptr = 0;}
                inline ParDescriptionSeq_var(ParDescriptionSeq *_obj) {_ptr = _obj;}
                ParDescriptionSeq_var(const ParDescriptionSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~ParDescriptionSeq_var();
                ParDescriptionSeq_var &operator=(ParDescriptionSeq *);
                ParDescriptionSeq_var &operator=(const ParDescriptionSeq_var &);
                inline ParameterDescription &operator[](ULong _index) {return (*_ptr)[_index];}
                inline ParDescriptionSeq *operator->() {return _ptr;}
                inline const ParDescriptionSeq *operator->() const {return _ptr;}
                inline const ParDescriptionSeq & in () const { return *_ptr; }
                inline ParDescriptionSeq & inout () { return *_ptr; }
                ParDescriptionSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ParDescriptionSeq * _retn ()
                {
                    ParDescriptionSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ParDescriptionSeq_ptr & ptr() { return _ptr; }
                inline operator ParDescriptionSeq&() { return *_ptr; }
                inline operator const ParDescriptionSeq&() const { return *_ptr; }
                inline operator ParDescriptionSeq_ptr &() { return _ptr; }
            private:
                ParDescriptionSeq *_ptr;
        };  // class ParDescriptionSeq_var

        class OBBEXPDLL ParDescriptionSeq_out
        {
            public:
                ParDescriptionSeq_out (ParDescriptionSeq *& p) : ptr_(p) { ptr_ = 0; }
                ParDescriptionSeq_out (ParDescriptionSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ParDescriptionSeq_out (const ParDescriptionSeq_out & a) : ptr_(a.ptr_) {}
                ParDescriptionSeq_out & operator=(const ParDescriptionSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ParDescriptionSeq_out & operator=(ParDescriptionSeq * p) {
                    ptr_ = p; return *this; }
                inline operator ParDescriptionSeq_ptr & () { return ptr_; }
                inline ParDescriptionSeq_ptr & ptr () { return ptr_; }
                inline ParDescriptionSeq_ptr operator->() { return ptr_; }
                inline ParameterDescription & operator[](ULong _index) {return (*ptr_)[_index]; }
            private:
                ParDescriptionSeq_ptr & ptr_;
                void operator=(const ParDescriptionSeq_var &);

        };  // class ParDescriptionSeq_out
        static const TypeCode_ptr _tc_ParDescriptionSeq;
        typedef Char * ContextIdentifier;
        typedef String_out ContextIdentifier_out;
        typedef String_var ContextIdentifier_var;
        static const TypeCode_ptr _tc_ContextIdentifier;


        class OBBEXPDLL ContextIdSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(ContextIdentifier _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(ContextIdentifier _ptr);
                        operator ContextIdentifier() const;
                        operator ContextIdentifier ();
                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static ContextIdentifier allocbuf(ULong _nelems);
                        static void freebuf(ContextIdentifier _ptr);

                    private:
                        ContextIdentifier _data;
                        Boolean _release;
                };  // class _ForSeq_var

                ContextIdSeq();

                ContextIdSeq(ULong _max);

                ContextIdSeq
                (
                    ULong _max,
                    ULong _length,
                    ContextIdentifier *_value,
                    Boolean _relse = CORBA_FALSE
                );

                ContextIdSeq(const ContextIdSeq &_ptr);

                ~ContextIdSeq();

                ContextIdSeq &operator=(const ContextIdSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static ContextIdentifier *allocbuf(ULong _nelems);
                static void freebuf(ContextIdentifier *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class ContextIdSeq

        typedef	ContextIdSeq *	ContextIdSeq_ptr;
        class OBBEXPDLL ContextIdSeq_var
        {
            public:
                inline ContextIdSeq_var() {_ptr = 0;}
                inline ContextIdSeq_var(ContextIdSeq *_obj) {_ptr = _obj;}
                ContextIdSeq_var(const ContextIdSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~ContextIdSeq_var();
                ContextIdSeq_var &operator=(ContextIdSeq *);
                ContextIdSeq_var &operator=(const ContextIdSeq_var &);
                inline ContextIdSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline ContextIdSeq *operator->() {return _ptr;}
                inline const ContextIdSeq *operator->() const {return _ptr;}
                inline const ContextIdSeq & in () const { return *_ptr; }
                inline ContextIdSeq & inout () { return *_ptr; }
                ContextIdSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ContextIdSeq * _retn ()
                {
                    ContextIdSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ContextIdSeq_ptr & ptr() { return _ptr; }
                inline operator ContextIdSeq&() { return *_ptr; }
                inline operator const ContextIdSeq&() const { return *_ptr; }
                inline operator ContextIdSeq_ptr &() { return _ptr; }
            private:
                ContextIdSeq *_ptr;
        };  // class ContextIdSeq_var

        class OBBEXPDLL ContextIdSeq_out
        {
            public:
                ContextIdSeq_out (ContextIdSeq *& p) : ptr_(p) { ptr_ = 0; }
                ContextIdSeq_out (ContextIdSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ContextIdSeq_out (const ContextIdSeq_out & a) : ptr_(a.ptr_) {}
                ContextIdSeq_out & operator=(const ContextIdSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ContextIdSeq_out & operator=(ContextIdSeq * p) {
                    ptr_ = p; return *this; }
                inline operator ContextIdSeq_ptr & () { return ptr_; }
                inline ContextIdSeq_ptr & ptr () { return ptr_; }
                inline ContextIdSeq_ptr operator->() { return ptr_; }
                inline ContextIdSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                ContextIdSeq_ptr & ptr_;
                void operator=(const ContextIdSeq_var &);

        };  // class ContextIdSeq_out
        static const TypeCode_ptr _tc_ContextIdSeq;


        class OBBEXPDLL ExceptionDefSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(ExceptionDef_ptr _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(ExceptionDef_ptr _ptr);
                        operator ExceptionDef_ptr() const;
                        operator ExceptionDef_ptr &();
                        ExceptionDef_ptr operator->();

                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static ExceptionDef_ptr allocbuf(ULong _nelems);
                        static void freebuf(ExceptionDef_ptr _ptr);

                    private:
                        ExceptionDef_ptr _data;
                        Boolean _release;
                };  // class _ForSeq_var

                ExceptionDefSeq();

                ExceptionDefSeq(ULong _max);

                ExceptionDefSeq
                (
                    ULong _max,
                    ULong _length,
                    ExceptionDef_ptr *_value,
                    Boolean _relse = CORBA_FALSE
                );

                ExceptionDefSeq(const ExceptionDefSeq &_ptr);

                ~ExceptionDefSeq();

                ExceptionDefSeq &operator=(const ExceptionDefSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static ExceptionDef_ptr *allocbuf(ULong _nelems);
                static void freebuf(ExceptionDef_ptr *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class ExceptionDefSeq

        typedef	ExceptionDefSeq *	ExceptionDefSeq_ptr;
        class OBBEXPDLL ExceptionDefSeq_var
        {
            public:
                inline ExceptionDefSeq_var() {_ptr = 0;}
                inline ExceptionDefSeq_var(ExceptionDefSeq *_obj) {_ptr = _obj;}
                ExceptionDefSeq_var(const ExceptionDefSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~ExceptionDefSeq_var();
                ExceptionDefSeq_var &operator=(ExceptionDefSeq *);
                ExceptionDefSeq_var &operator=(const ExceptionDefSeq_var &);
                inline ExceptionDefSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline ExceptionDefSeq *operator->() {return _ptr;}
                inline const ExceptionDefSeq *operator->() const {return _ptr;}
                inline const ExceptionDefSeq & in () const { return *_ptr; }
                inline ExceptionDefSeq & inout () { return *_ptr; }
                ExceptionDefSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ExceptionDefSeq * _retn ()
                {
                    ExceptionDefSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ExceptionDefSeq_ptr & ptr() { return _ptr; }
                inline operator ExceptionDefSeq&() { return *_ptr; }
                inline operator const ExceptionDefSeq&() const { return *_ptr; }
                inline operator ExceptionDefSeq_ptr &() { return _ptr; }
            private:
                ExceptionDefSeq *_ptr;
        };  // class ExceptionDefSeq_var

        class OBBEXPDLL ExceptionDefSeq_out
        {
            public:
                ExceptionDefSeq_out (ExceptionDefSeq *& p) : ptr_(p) { ptr_ = 0; }
                ExceptionDefSeq_out (ExceptionDefSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ExceptionDefSeq_out (const ExceptionDefSeq_out & a) : ptr_(a.ptr_) {}
                ExceptionDefSeq_out & operator=(const ExceptionDefSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ExceptionDefSeq_out & operator=(ExceptionDefSeq * p) {
                    ptr_ = p; return *this; }
                inline operator ExceptionDefSeq_ptr & () { return ptr_; }
                inline ExceptionDefSeq_ptr & ptr () { return ptr_; }
                inline ExceptionDefSeq_ptr operator->() { return ptr_; }
                inline ExceptionDefSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                ExceptionDefSeq_ptr & ptr_;
                void operator=(const ExceptionDefSeq_var &);

        };  // class ExceptionDefSeq_out
        static const TypeCode_ptr _tc_ExceptionDefSeq;


        class OBBEXPDLL ExcDescriptionSeq
        {
            public:
                ExcDescriptionSeq();

                ExcDescriptionSeq(ULong _max);

                ExcDescriptionSeq
                (
                    ULong _max,
                    ULong _length,
                    ExceptionDescription *_value,
                    Boolean _relse = CORBA_FALSE
                );

                ExcDescriptionSeq(const ExcDescriptionSeq &_ptr);

                ~ExcDescriptionSeq();

                ExcDescriptionSeq &operator=(const ExcDescriptionSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline ExceptionDescription &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const ExceptionDescription &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const ExceptionDescription &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static ExceptionDescription *allocbuf(ULong _nelems);
                static void freebuf(ExceptionDescription *_ptr);

                inline ExceptionDescription * OBB__GetData() { return _data; }
            private:
                ExceptionDescription *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class ExcDescriptionSeq

        typedef	ExcDescriptionSeq *	ExcDescriptionSeq_ptr;
        class OBBEXPDLL ExcDescriptionSeq_var
        {
            public:
                inline ExcDescriptionSeq_var() {_ptr = 0;}
                inline ExcDescriptionSeq_var(ExcDescriptionSeq *_obj) {_ptr = _obj;}
                ExcDescriptionSeq_var(const ExcDescriptionSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~ExcDescriptionSeq_var();
                ExcDescriptionSeq_var &operator=(ExcDescriptionSeq *);
                ExcDescriptionSeq_var &operator=(const ExcDescriptionSeq_var &);
                inline ExceptionDescription &operator[](ULong _index) {return (*_ptr)[_index];}
                inline ExcDescriptionSeq *operator->() {return _ptr;}
                inline const ExcDescriptionSeq *operator->() const {return _ptr;}
                inline const ExcDescriptionSeq & in () const { return *_ptr; }
                inline ExcDescriptionSeq & inout () { return *_ptr; }
                ExcDescriptionSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ExcDescriptionSeq * _retn ()
                {
                    ExcDescriptionSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ExcDescriptionSeq_ptr & ptr() { return _ptr; }
                inline operator ExcDescriptionSeq&() { return *_ptr; }
                inline operator const ExcDescriptionSeq&() const { return *_ptr; }
                inline operator ExcDescriptionSeq_ptr &() { return _ptr; }
            private:
                ExcDescriptionSeq *_ptr;
        };  // class ExcDescriptionSeq_var

        class OBBEXPDLL ExcDescriptionSeq_out
        {
            public:
                ExcDescriptionSeq_out (ExcDescriptionSeq *& p) : ptr_(p) { ptr_ = 0; }
                ExcDescriptionSeq_out (ExcDescriptionSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ExcDescriptionSeq_out (const ExcDescriptionSeq_out & a) : ptr_(a.ptr_) {}
                ExcDescriptionSeq_out & operator=(const ExcDescriptionSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ExcDescriptionSeq_out & operator=(ExcDescriptionSeq * p) {
                    ptr_ = p; return *this; }
                inline operator ExcDescriptionSeq_ptr & () { return ptr_; }
                inline ExcDescriptionSeq_ptr & ptr () { return ptr_; }
                inline ExcDescriptionSeq_ptr operator->() { return ptr_; }
                inline ExceptionDescription & operator[](ULong _index) {return (*ptr_)[_index]; }
            private:
                ExcDescriptionSeq_ptr & ptr_;
                void operator=(const ExcDescriptionSeq_var &);

        };  // class ExcDescriptionSeq_out
        static const TypeCode_ptr _tc_ExcDescriptionSeq;


        static const TypeCode_ptr _tc_OperationDef;
        class OBBEXPDLL OperationDef : public virtual  Contained
         {
            public:
                static OperationDef_ptr _duplicate(OperationDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static OperationDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static OperationDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual TypeCode_ptr result (); 

                virtual IDLType_ptr result_def (); 

                virtual void result_def (
                    IDLType_ptr result_def); 

                virtual ParDescriptionSeq * params (); 

                virtual void params (
                     const ParDescriptionSeq & params); 

                virtual OperationMode mode (); 

                virtual void mode (
                    OperationMode mode); 

                virtual ContextIdSeq * contexts (); 

                virtual void contexts (
                     const ContextIdSeq & contexts); 

                virtual ExceptionDefSeq * exceptions (); 

                virtual void exceptions (
                     const ExceptionDefSeq & exceptions); 

            protected:
                OperationDef(Object_ptr obj = 0);
                virtual ~OperationDef(){ }

            private:
                OperationDef( const OperationDef&) { }
                void operator=(const OperationDef&) { }
                ORB_ptr pORB;
        };  // class OperationDef



        class OBBEXPDLL OperationDef_out
         {
            public:
                OperationDef_out (OperationDef_ptr & p);
                OperationDef_out (OperationDef_var & p);
                OperationDef_out (const OperationDef_out & p) : ptr_(p.ptr_) {}
                OperationDef_out & operator=(const OperationDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                OperationDef_out & operator=(const OperationDef_var & a);
                OperationDef_out & operator=(OperationDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator OperationDef_ptr & () { return ptr_; }
                inline OperationDef_ptr & ptr () { return ptr_; }
                inline OperationDef_ptr operator->() { return ptr_; }
            private:
                OperationDef_ptr & ptr_;
        };  // class OperationDef_out



        struct OBBEXPDLL OperationDescription {
            String_var name;
            String_var id;
            String_var defined_in;
            String_var version;


             TypeCode_var result;


             OperationMode mode;


             ContextIdSeq contexts;


             ParDescriptionSeq parameters;


             ExcDescriptionSeq exceptions;
            OperationDescription &operator=(const OperationDescription &_obj);
        };
        typedef	OperationDescription *	OperationDescription_ptr;
        class OBBEXPDLL OperationDescription_var
        {
            public:
                inline OperationDescription_var() {_ptr = 0;}
                inline OperationDescription_var(OperationDescription *_obj) {_ptr = _obj;}
                OperationDescription_var(const OperationDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~OperationDescription_var();
                OperationDescription_var &operator=(OperationDescription *);
                OperationDescription_var &operator=(const OperationDescription_var &);
                inline OperationDescription *operator->() {return _ptr;}
                inline const OperationDescription *operator->() const {return _ptr;}
                inline const OperationDescription & in () const { return *_ptr; }
                inline OperationDescription & inout () { return *_ptr; }
                OperationDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                OperationDescription * _retn ()
                {
                    OperationDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline OperationDescription_ptr & ptr() { return _ptr; }
                inline operator OperationDescription&() { return *_ptr; }
                inline operator const OperationDescription&() const { return *_ptr; }
                inline operator OperationDescription_ptr &() { return _ptr; }
            private:
                OperationDescription *_ptr;
        };  // class OperationDescription_var

        class OBBEXPDLL OperationDescription_out
        {
            public:
                OperationDescription_out (OperationDescription *& p) : ptr_(p) { ptr_ = 0; }
                OperationDescription_out (OperationDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                OperationDescription_out (const OperationDescription_out & a) : ptr_(a.ptr_) {}
                OperationDescription_out & operator=(const OperationDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                OperationDescription_out & operator=(OperationDescription * p) {
                    ptr_ = p; return *this; }
                inline operator OperationDescription_ptr & () { return ptr_; }
                inline OperationDescription_ptr & ptr () { return ptr_; }
                inline OperationDescription_ptr operator->() { return ptr_; }
            private:
                OperationDescription_ptr & ptr_;
                void operator=(const OperationDescription_var &);

        };  // class OperationDescription_out
        static const TypeCode_ptr _tc_OperationDescription;


        class OBBEXPDLL RepositoryIdSeq
        {
            public:


                class OBBEXPDLL _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(RepositoryId _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(RepositoryId _ptr);
                        operator RepositoryId() const;
                        operator RepositoryId ();
                        void OBB__release(Boolean _relse);
                        Boolean OBB__release();

                        static RepositoryId allocbuf(ULong _nelems);
                        static void freebuf(RepositoryId _ptr);

                    private:
                        RepositoryId _data;
                        Boolean _release;
                };  // class _ForSeq_var

                RepositoryIdSeq();

                RepositoryIdSeq(ULong _max);

                RepositoryIdSeq
                (
                    ULong _max,
                    ULong _length,
                    RepositoryId *_value,
                    Boolean _relse = CORBA_FALSE
                );

                RepositoryIdSeq(const RepositoryIdSeq &_ptr);

                ~RepositoryIdSeq();

                RepositoryIdSeq &operator=(const RepositoryIdSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline _ForSeq_var &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static RepositoryId *allocbuf(ULong _nelems);
                static void freebuf(RepositoryId *_ptr);

            private:
                _ForSeq_var *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
                static _ForSeq_var *OBB__allocbuf(ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class RepositoryIdSeq

        typedef	RepositoryIdSeq *	RepositoryIdSeq_ptr;
        class OBBEXPDLL RepositoryIdSeq_var
        {
            public:
                inline RepositoryIdSeq_var() {_ptr = 0;}
                inline RepositoryIdSeq_var(RepositoryIdSeq *_obj) {_ptr = _obj;}
                RepositoryIdSeq_var(const RepositoryIdSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~RepositoryIdSeq_var();
                RepositoryIdSeq_var &operator=(RepositoryIdSeq *);
                RepositoryIdSeq_var &operator=(const RepositoryIdSeq_var &);
                inline RepositoryIdSeq::_ForSeq_var &operator[](ULong _index) {return (*_ptr)[_index];}
                inline RepositoryIdSeq *operator->() {return _ptr;}
                inline const RepositoryIdSeq *operator->() const {return _ptr;}
                inline const RepositoryIdSeq & in () const { return *_ptr; }
                inline RepositoryIdSeq & inout () { return *_ptr; }
                RepositoryIdSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                RepositoryIdSeq * _retn ()
                {
                    RepositoryIdSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline RepositoryIdSeq_ptr & ptr() { return _ptr; }
                inline operator RepositoryIdSeq&() { return *_ptr; }
                inline operator const RepositoryIdSeq&() const { return *_ptr; }
                inline operator RepositoryIdSeq_ptr &() { return _ptr; }
            private:
                RepositoryIdSeq *_ptr;
        };  // class RepositoryIdSeq_var

        class OBBEXPDLL RepositoryIdSeq_out
        {
            public:
                RepositoryIdSeq_out (RepositoryIdSeq *& p) : ptr_(p) { ptr_ = 0; }
                RepositoryIdSeq_out (RepositoryIdSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                RepositoryIdSeq_out (const RepositoryIdSeq_out & a) : ptr_(a.ptr_) {}
                RepositoryIdSeq_out & operator=(const RepositoryIdSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                RepositoryIdSeq_out & operator=(RepositoryIdSeq * p) {
                    ptr_ = p; return *this; }
                inline operator RepositoryIdSeq_ptr & () { return ptr_; }
                inline RepositoryIdSeq_ptr & ptr () { return ptr_; }
                inline RepositoryIdSeq_ptr operator->() { return ptr_; }
                inline RepositoryIdSeq::_ForSeq_var & operator[](ULong _index) {return ((*ptr_)[_index]);}
            private:
                RepositoryIdSeq_ptr & ptr_;
                void operator=(const RepositoryIdSeq_var &);

        };  // class RepositoryIdSeq_out
        static const TypeCode_ptr _tc_RepositoryIdSeq;


        class OBBEXPDLL OpDescriptionSeq
        {
            public:
                OpDescriptionSeq();

                OpDescriptionSeq(ULong _max);

                OpDescriptionSeq
                (
                    ULong _max,
                    ULong _length,
                    OperationDescription *_value,
                    Boolean _relse = CORBA_FALSE
                );

                OpDescriptionSeq(const OpDescriptionSeq &_ptr);

                ~OpDescriptionSeq();

                OpDescriptionSeq &operator=(const OpDescriptionSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline OperationDescription &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const OperationDescription &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const OperationDescription &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static OperationDescription *allocbuf(ULong _nelems);
                static void freebuf(OperationDescription *_ptr);

                inline OperationDescription * OBB__GetData() { return _data; }
            private:
                OperationDescription *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class OpDescriptionSeq

        typedef	OpDescriptionSeq *	OpDescriptionSeq_ptr;
        class OBBEXPDLL OpDescriptionSeq_var
        {
            public:
                inline OpDescriptionSeq_var() {_ptr = 0;}
                inline OpDescriptionSeq_var(OpDescriptionSeq *_obj) {_ptr = _obj;}
                OpDescriptionSeq_var(const OpDescriptionSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~OpDescriptionSeq_var();
                OpDescriptionSeq_var &operator=(OpDescriptionSeq *);
                OpDescriptionSeq_var &operator=(const OpDescriptionSeq_var &);
                inline OperationDescription &operator[](ULong _index) {return (*_ptr)[_index];}
                inline OpDescriptionSeq *operator->() {return _ptr;}
                inline const OpDescriptionSeq *operator->() const {return _ptr;}
                inline const OpDescriptionSeq & in () const { return *_ptr; }
                inline OpDescriptionSeq & inout () { return *_ptr; }
                OpDescriptionSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                OpDescriptionSeq * _retn ()
                {
                    OpDescriptionSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline OpDescriptionSeq_ptr & ptr() { return _ptr; }
                inline operator OpDescriptionSeq&() { return *_ptr; }
                inline operator const OpDescriptionSeq&() const { return *_ptr; }
                inline operator OpDescriptionSeq_ptr &() { return _ptr; }
            private:
                OpDescriptionSeq *_ptr;
        };  // class OpDescriptionSeq_var

        class OBBEXPDLL OpDescriptionSeq_out
        {
            public:
                OpDescriptionSeq_out (OpDescriptionSeq *& p) : ptr_(p) { ptr_ = 0; }
                OpDescriptionSeq_out (OpDescriptionSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                OpDescriptionSeq_out (const OpDescriptionSeq_out & a) : ptr_(a.ptr_) {}
                OpDescriptionSeq_out & operator=(const OpDescriptionSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                OpDescriptionSeq_out & operator=(OpDescriptionSeq * p) {
                    ptr_ = p; return *this; }
                inline operator OpDescriptionSeq_ptr & () { return ptr_; }
                inline OpDescriptionSeq_ptr & ptr () { return ptr_; }
                inline OpDescriptionSeq_ptr operator->() { return ptr_; }
                inline OperationDescription & operator[](ULong _index) {return (*ptr_)[_index]; }
            private:
                OpDescriptionSeq_ptr & ptr_;
                void operator=(const OpDescriptionSeq_var &);

        };  // class OpDescriptionSeq_out
        static const TypeCode_ptr _tc_OpDescriptionSeq;


        class OBBEXPDLL AttrDescriptionSeq
        {
            public:
                AttrDescriptionSeq();

                AttrDescriptionSeq(ULong _max);

                AttrDescriptionSeq
                (
                    ULong _max,
                    ULong _length,
                    AttributeDescription *_value,
                    Boolean _relse = CORBA_FALSE
                );

                AttrDescriptionSeq(const AttrDescriptionSeq &_ptr);

                ~AttrDescriptionSeq();

                AttrDescriptionSeq &operator=(const AttrDescriptionSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline AttributeDescription &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const AttributeDescription &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const AttributeDescription &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static AttributeDescription *allocbuf(ULong _nelems);
                static void freebuf(AttributeDescription *_ptr);

                inline AttributeDescription * OBB__GetData() { return _data; }
            private:
                AttributeDescription *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class AttrDescriptionSeq

        typedef	AttrDescriptionSeq *	AttrDescriptionSeq_ptr;
        class OBBEXPDLL AttrDescriptionSeq_var
        {
            public:
                inline AttrDescriptionSeq_var() {_ptr = 0;}
                inline AttrDescriptionSeq_var(AttrDescriptionSeq *_obj) {_ptr = _obj;}
                AttrDescriptionSeq_var(const AttrDescriptionSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~AttrDescriptionSeq_var();
                AttrDescriptionSeq_var &operator=(AttrDescriptionSeq *);
                AttrDescriptionSeq_var &operator=(const AttrDescriptionSeq_var &);
                inline AttributeDescription &operator[](ULong _index) {return (*_ptr)[_index];}
                inline AttrDescriptionSeq *operator->() {return _ptr;}
                inline const AttrDescriptionSeq *operator->() const {return _ptr;}
                inline const AttrDescriptionSeq & in () const { return *_ptr; }
                inline AttrDescriptionSeq & inout () { return *_ptr; }
                AttrDescriptionSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                AttrDescriptionSeq * _retn ()
                {
                    AttrDescriptionSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline AttrDescriptionSeq_ptr & ptr() { return _ptr; }
                inline operator AttrDescriptionSeq&() { return *_ptr; }
                inline operator const AttrDescriptionSeq&() const { return *_ptr; }
                inline operator AttrDescriptionSeq_ptr &() { return _ptr; }
            private:
                AttrDescriptionSeq *_ptr;
        };  // class AttrDescriptionSeq_var

        class OBBEXPDLL AttrDescriptionSeq_out
        {
            public:
                AttrDescriptionSeq_out (AttrDescriptionSeq *& p) : ptr_(p) { ptr_ = 0; }
                AttrDescriptionSeq_out (AttrDescriptionSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                AttrDescriptionSeq_out (const AttrDescriptionSeq_out & a) : ptr_(a.ptr_) {}
                AttrDescriptionSeq_out & operator=(const AttrDescriptionSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                AttrDescriptionSeq_out & operator=(AttrDescriptionSeq * p) {
                    ptr_ = p; return *this; }
                inline operator AttrDescriptionSeq_ptr & () { return ptr_; }
                inline AttrDescriptionSeq_ptr & ptr () { return ptr_; }
                inline AttrDescriptionSeq_ptr operator->() { return ptr_; }
                inline AttributeDescription & operator[](ULong _index) {return (*ptr_)[_index]; }
            private:
                AttrDescriptionSeq_ptr & ptr_;
                void operator=(const AttrDescriptionSeq_var &);

        };  // class AttrDescriptionSeq_out
        static const TypeCode_ptr _tc_AttrDescriptionSeq;


        static const TypeCode_ptr _tc_InterfaceDef;
        class OBBEXPDLL InterfaceDef : public virtual  Container, public virtual  Contained, public virtual  IDLType
         {
            public:


                struct OBBEXPDLL FullInterfaceDescription {
                    String_var name;
                    String_var id;
                    String_var defined_in;
                    String_var version;


                     OpDescriptionSeq operations;


                     AttrDescriptionSeq attributes;


                     RepositoryIdSeq base_interfaces;


                     TypeCode_var type;
                    FullInterfaceDescription &operator=(const FullInterfaceDescription &_obj);
                };
                typedef	FullInterfaceDescription *	FullInterfaceDescription_ptr;
                class OBBEXPDLL FullInterfaceDescription_var
                {
                    public:
                        inline FullInterfaceDescription_var() {_ptr = 0;}
                        inline FullInterfaceDescription_var(FullInterfaceDescription *_obj) {_ptr = _obj;}
                        FullInterfaceDescription_var(const FullInterfaceDescription_var &_obj) {_ptr = 0; *this = _obj;}
                        ~FullInterfaceDescription_var();
                        FullInterfaceDescription_var &operator=(FullInterfaceDescription *);
                        FullInterfaceDescription_var &operator=(const FullInterfaceDescription_var &);
                        inline FullInterfaceDescription *operator->() {return _ptr;}
                        inline const FullInterfaceDescription *operator->() const {return _ptr;}
                        inline const FullInterfaceDescription & in () const { return *_ptr; }
                        inline FullInterfaceDescription & inout () { return *_ptr; }
                        FullInterfaceDescription *& out ()
                        {
                            delete _ptr;
                            _ptr=0;
                            return _ptr;
                        }
                        FullInterfaceDescription * _retn ()
                        {
                            FullInterfaceDescription *tmp = _ptr;
                            _ptr = 0;
                            return tmp;
                        }
                        inline FullInterfaceDescription_ptr & ptr() { return _ptr; }
                        inline operator FullInterfaceDescription&() { return *_ptr; }
                        inline operator const FullInterfaceDescription&() const { return *_ptr; }
                        inline operator FullInterfaceDescription_ptr &() { return _ptr; }
                    private:
                        FullInterfaceDescription *_ptr;
                };  // class FullInterfaceDescription_var

                class OBBEXPDLL FullInterfaceDescription_out
                {
                    public:
                        FullInterfaceDescription_out (FullInterfaceDescription *& p) : ptr_(p) { ptr_ = 0; }
                        FullInterfaceDescription_out (FullInterfaceDescription_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        FullInterfaceDescription_out (const FullInterfaceDescription_out & a) : ptr_(a.ptr_) {}
                        FullInterfaceDescription_out & operator=(const FullInterfaceDescription_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        FullInterfaceDescription_out & operator=(FullInterfaceDescription * p) {
                            ptr_ = p; return *this; }
                        inline operator FullInterfaceDescription_ptr & () { return ptr_; }
                        inline FullInterfaceDescription_ptr & ptr () { return ptr_; }
                        inline FullInterfaceDescription_ptr operator->() { return ptr_; }
                    private:
                        FullInterfaceDescription_ptr & ptr_;
                        void operator=(const FullInterfaceDescription_var &);

                };  // class FullInterfaceDescription_out
                static const TypeCode_ptr _tc_FullInterfaceDescription;
                static InterfaceDef_ptr _duplicate(InterfaceDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static InterfaceDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static InterfaceDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Boolean is_a (
                    const char * interface_id); 

                virtual FullInterfaceDescription * describe_interface (); 

                virtual AttributeDef_ptr create_attribute (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr type,
                    AttributeMode mode); 

                virtual OperationDef_ptr create_operation (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr result,
                    OperationMode mode,
                     const ParDescriptionSeq & params,
                     const ExceptionDefSeq & exceptions,
                     const ContextIdSeq & contexts); 

                virtual InterfaceDefSeq * base_interfaces (); 

                virtual void base_interfaces (
                     const InterfaceDefSeq & base_interfaces); 

            protected:
                InterfaceDef(Object_ptr obj = 0);
                virtual ~InterfaceDef(){ }

            private:
                InterfaceDef( const InterfaceDef&) { }
                void operator=(const InterfaceDef&) { }
                ORB_ptr pORB;
        };  // class InterfaceDef



        class OBBEXPDLL InterfaceDef_out
         {
            public:
                InterfaceDef_out (InterfaceDef_ptr & p);
                InterfaceDef_out (InterfaceDef_var & p);
                InterfaceDef_out (const InterfaceDef_out & p) : ptr_(p.ptr_) {}
                InterfaceDef_out & operator=(const InterfaceDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                InterfaceDef_out & operator=(const InterfaceDef_var & a);
                InterfaceDef_out & operator=(InterfaceDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator InterfaceDef_ptr & () { return ptr_; }
                inline InterfaceDef_ptr & ptr () { return ptr_; }
                inline InterfaceDef_ptr operator->() { return ptr_; }
            private:
                InterfaceDef_ptr & ptr_;
        };  // class InterfaceDef_out



        struct OBBEXPDLL InterfaceDescription {
            String_var name;
            String_var id;
            String_var defined_in;
            String_var version;


             RepositoryIdSeq base_interfaces;
            InterfaceDescription &operator=(const InterfaceDescription &_obj);
        };
        typedef	InterfaceDescription *	InterfaceDescription_ptr;
        class OBBEXPDLL InterfaceDescription_var
        {
            public:
                inline InterfaceDescription_var() {_ptr = 0;}
                inline InterfaceDescription_var(InterfaceDescription *_obj) {_ptr = _obj;}
                InterfaceDescription_var(const InterfaceDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~InterfaceDescription_var();
                InterfaceDescription_var &operator=(InterfaceDescription *);
                InterfaceDescription_var &operator=(const InterfaceDescription_var &);
                inline InterfaceDescription *operator->() {return _ptr;}
                inline const InterfaceDescription *operator->() const {return _ptr;}
                inline const InterfaceDescription & in () const { return *_ptr; }
                inline InterfaceDescription & inout () { return *_ptr; }
                InterfaceDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InterfaceDescription * _retn ()
                {
                    InterfaceDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InterfaceDescription_ptr & ptr() { return _ptr; }
                inline operator InterfaceDescription&() { return *_ptr; }
                inline operator const InterfaceDescription&() const { return *_ptr; }
                inline operator InterfaceDescription_ptr &() { return _ptr; }
            private:
                InterfaceDescription *_ptr;
        };  // class InterfaceDescription_var

        class OBBEXPDLL InterfaceDescription_out
        {
            public:
                InterfaceDescription_out (InterfaceDescription *& p) : ptr_(p) { ptr_ = 0; }
                InterfaceDescription_out (InterfaceDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InterfaceDescription_out (const InterfaceDescription_out & a) : ptr_(a.ptr_) {}
                InterfaceDescription_out & operator=(const InterfaceDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InterfaceDescription_out & operator=(InterfaceDescription * p) {
                    ptr_ = p; return *this; }
                inline operator InterfaceDescription_ptr & () { return ptr_; }
                inline InterfaceDescription_ptr & ptr () { return ptr_; }
                inline InterfaceDescription_ptr operator->() { return ptr_; }
            private:
                InterfaceDescription_ptr & ptr_;
                void operator=(const InterfaceDescription_var &);

        };  // class InterfaceDescription_out
        static const TypeCode_ptr _tc_InterfaceDescription;
        typedef Short Visibility;
        typedef Short_out Visibility_out;
        static const TypeCode_ptr _tc_Visibility;
        static const Visibility PRIVATE_MEMBER ;
        static const Visibility PUBLIC_MEMBER ;


        struct OBBEXPDLL ValueMember {
            String_var name;
            String_var id;
            String_var defined_in;
            String_var version;


             TypeCode_var type;


             IDLType_var type_def;
             Visibility access;
            ValueMember &operator=(const ValueMember &_obj);
        };
        typedef	ValueMember *	ValueMember_ptr;
        class OBBEXPDLL ValueMember_var
        {
            public:
                inline ValueMember_var() {_ptr = 0;}
                inline ValueMember_var(ValueMember *_obj) {_ptr = _obj;}
                ValueMember_var(const ValueMember_var &_obj) {_ptr = 0; *this = _obj;}
                ~ValueMember_var();
                ValueMember_var &operator=(ValueMember *);
                ValueMember_var &operator=(const ValueMember_var &);
                inline ValueMember *operator->() {return _ptr;}
                inline const ValueMember *operator->() const {return _ptr;}
                inline const ValueMember & in () const { return *_ptr; }
                inline ValueMember & inout () { return *_ptr; }
                ValueMember *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ValueMember * _retn ()
                {
                    ValueMember *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ValueMember_ptr & ptr() { return _ptr; }
                inline operator ValueMember&() { return *_ptr; }
                inline operator const ValueMember&() const { return *_ptr; }
                inline operator ValueMember_ptr &() { return _ptr; }
            private:
                ValueMember *_ptr;
        };  // class ValueMember_var

        class OBBEXPDLL ValueMember_out
        {
            public:
                ValueMember_out (ValueMember *& p) : ptr_(p) { ptr_ = 0; }
                ValueMember_out (ValueMember_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ValueMember_out (const ValueMember_out & a) : ptr_(a.ptr_) {}
                ValueMember_out & operator=(const ValueMember_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ValueMember_out & operator=(ValueMember * p) {
                    ptr_ = p; return *this; }
                inline operator ValueMember_ptr & () { return ptr_; }
                inline ValueMember_ptr & ptr () { return ptr_; }
                inline ValueMember_ptr operator->() { return ptr_; }
            private:
                ValueMember_ptr & ptr_;
                void operator=(const ValueMember_var &);

        };  // class ValueMember_out
        static const TypeCode_ptr _tc_ValueMember;


        class OBBEXPDLL ValueMemberSeq
        {
            public:
                ValueMemberSeq();

                ValueMemberSeq(ULong _max);

                ValueMemberSeq
                (
                    ULong _max,
                    ULong _length,
                    ValueMember *_value,
                    Boolean _relse = CORBA_FALSE
                );

                ValueMemberSeq(const ValueMemberSeq &_ptr);

                ~ValueMemberSeq();

                ValueMemberSeq &operator=(const ValueMemberSeq& _ptr);

                inline ULong maximum() const {return _maximum;}

                void length(ULong);
                inline ULong length() const {return _current;}

                inline ValueMember &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const ValueMember &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM();
#ifdef WIN32
                            return (const ValueMember &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static ValueMember *allocbuf(ULong _nelems);
                static void freebuf(ValueMember *_ptr);

                inline ValueMember * OBB__GetData() { return _data; }
            private:
                ValueMember *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class ValueMemberSeq

        typedef	ValueMemberSeq *	ValueMemberSeq_ptr;
        class OBBEXPDLL ValueMemberSeq_var
        {
            public:
                inline ValueMemberSeq_var() {_ptr = 0;}
                inline ValueMemberSeq_var(ValueMemberSeq *_obj) {_ptr = _obj;}
                ValueMemberSeq_var(const ValueMemberSeq_var &_obj) {_ptr = 0; *this = _obj;}
                ~ValueMemberSeq_var();
                ValueMemberSeq_var &operator=(ValueMemberSeq *);
                ValueMemberSeq_var &operator=(const ValueMemberSeq_var &);
                inline ValueMember &operator[](ULong _index) {return (*_ptr)[_index];}
                inline ValueMemberSeq *operator->() {return _ptr;}
                inline const ValueMemberSeq *operator->() const {return _ptr;}
                inline const ValueMemberSeq & in () const { return *_ptr; }
                inline ValueMemberSeq & inout () { return *_ptr; }
                ValueMemberSeq *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ValueMemberSeq * _retn ()
                {
                    ValueMemberSeq *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ValueMemberSeq_ptr & ptr() { return _ptr; }
                inline operator ValueMemberSeq&() { return *_ptr; }
                inline operator const ValueMemberSeq&() const { return *_ptr; }
                inline operator ValueMemberSeq_ptr &() { return _ptr; }
            private:
                ValueMemberSeq *_ptr;
        };  // class ValueMemberSeq_var

        class OBBEXPDLL ValueMemberSeq_out
        {
            public:
                ValueMemberSeq_out (ValueMemberSeq *& p) : ptr_(p) { ptr_ = 0; }
                ValueMemberSeq_out (ValueMemberSeq_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ValueMemberSeq_out (const ValueMemberSeq_out & a) : ptr_(a.ptr_) {}
                ValueMemberSeq_out & operator=(const ValueMemberSeq_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ValueMemberSeq_out & operator=(ValueMemberSeq * p) {
                    ptr_ = p; return *this; }
                inline operator ValueMemberSeq_ptr & () { return ptr_; }
                inline ValueMemberSeq_ptr & ptr () { return ptr_; }
                inline ValueMemberSeq_ptr operator->() { return ptr_; }
                inline ValueMember & operator[](ULong _index) {return (*ptr_)[_index]; }
            private:
                ValueMemberSeq_ptr & ptr_;
                void operator=(const ValueMemberSeq_var &);

        };  // class ValueMemberSeq_out
        static const TypeCode_ptr _tc_ValueMemberSeq;


        static const TypeCode_ptr _tc_ValueMemberDef;
        class OBBEXPDLL ValueMemberDef : public virtual  Contained
         {
            public:
                static ValueMemberDef_ptr _duplicate(ValueMemberDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static ValueMemberDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static ValueMemberDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual TypeCode_ptr type (); 

                virtual IDLType_ptr type_def (); 

                virtual void type_def (
                    IDLType_ptr type_def); 

                virtual Visibility access (); 

                virtual void access (
                    Visibility access); 

            protected:
                ValueMemberDef(Object_ptr obj = 0);
                virtual ~ValueMemberDef(){ }

            private:
                ValueMemberDef( const ValueMemberDef&) { }
                void operator=(const ValueMemberDef&) { }
                ORB_ptr pORB;
        };  // class ValueMemberDef



        class OBBEXPDLL ValueMemberDef_out
         {
            public:
                ValueMemberDef_out (ValueMemberDef_ptr & p);
                ValueMemberDef_out (ValueMemberDef_var & p);
                ValueMemberDef_out (const ValueMemberDef_out & p) : ptr_(p.ptr_) {}
                ValueMemberDef_out & operator=(const ValueMemberDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                ValueMemberDef_out & operator=(const ValueMemberDef_var & a);
                ValueMemberDef_out & operator=(ValueMemberDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator ValueMemberDef_ptr & () { return ptr_; }
                inline ValueMemberDef_ptr & ptr () { return ptr_; }
                inline ValueMemberDef_ptr operator->() { return ptr_; }
            private:
                ValueMemberDef_ptr & ptr_;
        };  // class ValueMemberDef_out



        static const TypeCode_ptr _tc_ValueDef;
        class OBBEXPDLL ValueDef : public virtual  Container, public virtual  Contained, public virtual  IDLType
         {
            public:


                struct OBBEXPDLL FullValueDescription {
                    String_var name;
                    String_var id;
                     Boolean is_abstract;
                     Boolean is_custom;
                    String_var defined_in;
                    String_var version;


                     OpDescriptionSeq operations;


                     AttrDescriptionSeq attributes;


                     ValueMemberSeq members;


                     InitializerSeq initializers;


                     RepositoryIdSeq supported_interfaces;


                     RepositoryIdSeq abstract_base_values;
                     Boolean is_truncatable;
                    String_var base_value;


                     TypeCode_var type;
                    FullValueDescription &operator=(const FullValueDescription &_obj);
                };
                typedef	FullValueDescription *	FullValueDescription_ptr;
                class OBBEXPDLL FullValueDescription_var
                {
                    public:
                        inline FullValueDescription_var() {_ptr = 0;}
                        inline FullValueDescription_var(FullValueDescription *_obj) {_ptr = _obj;}
                        FullValueDescription_var(const FullValueDescription_var &_obj) {_ptr = 0; *this = _obj;}
                        ~FullValueDescription_var();
                        FullValueDescription_var &operator=(FullValueDescription *);
                        FullValueDescription_var &operator=(const FullValueDescription_var &);
                        inline FullValueDescription *operator->() {return _ptr;}
                        inline const FullValueDescription *operator->() const {return _ptr;}
                        inline const FullValueDescription & in () const { return *_ptr; }
                        inline FullValueDescription & inout () { return *_ptr; }
                        FullValueDescription *& out ()
                        {
                            delete _ptr;
                            _ptr=0;
                            return _ptr;
                        }
                        FullValueDescription * _retn ()
                        {
                            FullValueDescription *tmp = _ptr;
                            _ptr = 0;
                            return tmp;
                        }
                        inline FullValueDescription_ptr & ptr() { return _ptr; }
                        inline operator FullValueDescription&() { return *_ptr; }
                        inline operator const FullValueDescription&() const { return *_ptr; }
                        inline operator FullValueDescription_ptr &() { return _ptr; }
                    private:
                        FullValueDescription *_ptr;
                };  // class FullValueDescription_var

                class OBBEXPDLL FullValueDescription_out
                {
                    public:
                        FullValueDescription_out (FullValueDescription *& p) : ptr_(p) { ptr_ = 0; }
                        FullValueDescription_out (FullValueDescription_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        FullValueDescription_out (const FullValueDescription_out & a) : ptr_(a.ptr_) {}
                        FullValueDescription_out & operator=(const FullValueDescription_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        FullValueDescription_out & operator=(FullValueDescription * p) {
                            ptr_ = p; return *this; }
                        inline operator FullValueDescription_ptr & () { return ptr_; }
                        inline FullValueDescription_ptr & ptr () { return ptr_; }
                        inline FullValueDescription_ptr operator->() { return ptr_; }
                    private:
                        FullValueDescription_ptr & ptr_;
                        void operator=(const FullValueDescription_var &);

                };  // class FullValueDescription_out
                static const TypeCode_ptr _tc_FullValueDescription;
                static ValueDef_ptr _duplicate(ValueDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static ValueDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static ValueDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Boolean is_a (
                    const char * id); 

                virtual FullValueDescription * describe_value (); 

                virtual ValueMemberDef_ptr create_value_member (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr type,
                    Visibility access); 

                virtual AttributeDef_ptr create_attribute (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr type,
                    AttributeMode mode); 

                virtual OperationDef_ptr create_operation (
                    const char * id,
                    const char * name,
                    const char * version,
                    IDLType_ptr result,
                    OperationMode mode,
                     const ParDescriptionSeq & params,
                     const ExceptionDefSeq & exceptions,
                     const ContextIdSeq & contexts); 

                virtual InterfaceDefSeq * supported_interfaces (); 

                virtual void supported_interfaces (
                     const InterfaceDefSeq & supported_interfaces); 

                virtual InitializerSeq * initializers (); 

                virtual void initializers (
                     const InitializerSeq & initializers); 

                virtual ValueDef_ptr base_value (); 

                virtual void base_value (
                    ValueDef_ptr base_value); 

                virtual ValueDefSeq * abstract_base_values (); 

                virtual void abstract_base_values (
                     const ValueDefSeq & abstract_base_values); 

                virtual Boolean is_abstract (); 

                virtual void is_abstract (
                    Boolean is_abstract); 

                virtual Boolean is_custom (); 

                virtual void is_custom (
                    Boolean is_custom); 

                virtual Boolean is_truncatable (); 

                virtual void is_truncatable (
                    Boolean is_truncatable); 

            protected:
                ValueDef(Object_ptr obj = 0);
                virtual ~ValueDef(){ }

            private:
                ValueDef( const ValueDef&) { }
                void operator=(const ValueDef&) { }
                ORB_ptr pORB;
        };  // class ValueDef



        class OBBEXPDLL ValueDef_out
         {
            public:
                ValueDef_out (ValueDef_ptr & p);
                ValueDef_out (ValueDef_var & p);
                ValueDef_out (const ValueDef_out & p) : ptr_(p.ptr_) {}
                ValueDef_out & operator=(const ValueDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                ValueDef_out & operator=(const ValueDef_var & a);
                ValueDef_out & operator=(ValueDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator ValueDef_ptr & () { return ptr_; }
                inline ValueDef_ptr & ptr () { return ptr_; }
                inline ValueDef_ptr operator->() { return ptr_; }
            private:
                ValueDef_ptr & ptr_;
        };  // class ValueDef_out



        struct OBBEXPDLL ValueDescription {
            String_var name;
            String_var id;
             Boolean is_abstract;
             Boolean is_custom;
            String_var defined_in;
            String_var version;


             RepositoryIdSeq supported_interfaces;


             RepositoryIdSeq abstract_base_values;
             Boolean is_truncatable;
            String_var base_value;
            ValueDescription &operator=(const ValueDescription &_obj);
        };
        typedef	ValueDescription *	ValueDescription_ptr;
        class OBBEXPDLL ValueDescription_var
        {
            public:
                inline ValueDescription_var() {_ptr = 0;}
                inline ValueDescription_var(ValueDescription *_obj) {_ptr = _obj;}
                ValueDescription_var(const ValueDescription_var &_obj) {_ptr = 0; *this = _obj;}
                ~ValueDescription_var();
                ValueDescription_var &operator=(ValueDescription *);
                ValueDescription_var &operator=(const ValueDescription_var &);
                inline ValueDescription *operator->() {return _ptr;}
                inline const ValueDescription *operator->() const {return _ptr;}
                inline const ValueDescription & in () const { return *_ptr; }
                inline ValueDescription & inout () { return *_ptr; }
                ValueDescription *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ValueDescription * _retn ()
                {
                    ValueDescription *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ValueDescription_ptr & ptr() { return _ptr; }
                inline operator ValueDescription&() { return *_ptr; }
                inline operator const ValueDescription&() const { return *_ptr; }
                inline operator ValueDescription_ptr &() { return _ptr; }
            private:
                ValueDescription *_ptr;
        };  // class ValueDescription_var

        class OBBEXPDLL ValueDescription_out
        {
            public:
                ValueDescription_out (ValueDescription *& p) : ptr_(p) { ptr_ = 0; }
                ValueDescription_out (ValueDescription_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ValueDescription_out (const ValueDescription_out & a) : ptr_(a.ptr_) {}
                ValueDescription_out & operator=(const ValueDescription_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ValueDescription_out & operator=(ValueDescription * p) {
                    ptr_ = p; return *this; }
                inline operator ValueDescription_ptr & () { return ptr_; }
                inline ValueDescription_ptr & ptr () { return ptr_; }
                inline ValueDescription_ptr operator->() { return ptr_; }
            private:
                ValueDescription_ptr & ptr_;
                void operator=(const ValueDescription_var &);

        };  // class ValueDescription_out
        static const TypeCode_ptr _tc_ValueDescription;


        static const TypeCode_ptr _tc_ValueBoxDef;
        class OBBEXPDLL ValueBoxDef : public virtual  TypedefDef
         {
            public:
                static ValueBoxDef_ptr _duplicate(ValueBoxDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static ValueBoxDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static ValueBoxDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual IDLType_ptr original_type_def (); 

                virtual void original_type_def (
                    IDLType_ptr original_type_def); 

            protected:
                ValueBoxDef(Object_ptr obj = 0);
                virtual ~ValueBoxDef(){ }

            private:
                ValueBoxDef( const ValueBoxDef&) { }
                void operator=(const ValueBoxDef&) { }
                ORB_ptr pORB;
        };  // class ValueBoxDef



        class OBBEXPDLL ValueBoxDef_out
         {
            public:
                ValueBoxDef_out (ValueBoxDef_ptr & p);
                ValueBoxDef_out (ValueBoxDef_var & p);
                ValueBoxDef_out (const ValueBoxDef_out & p) : ptr_(p.ptr_) {}
                ValueBoxDef_out & operator=(const ValueBoxDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                ValueBoxDef_out & operator=(const ValueBoxDef_var & a);
                ValueBoxDef_out & operator=(ValueBoxDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator ValueBoxDef_ptr & () { return ptr_; }
                inline ValueBoxDef_ptr & ptr () { return ptr_; }
                inline ValueBoxDef_ptr operator->() { return ptr_; }
            private:
                ValueBoxDef_ptr & ptr_;
        };  // class ValueBoxDef_out



        static const TypeCode_ptr _tc_AbstractInterfaceDef;
        class OBBEXPDLL AbstractInterfaceDef : public virtual  InterfaceDef
         {
            public:
                static AbstractInterfaceDef_ptr _duplicate(AbstractInterfaceDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static AbstractInterfaceDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static AbstractInterfaceDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

            protected:
                AbstractInterfaceDef(Object_ptr obj = 0);
                virtual ~AbstractInterfaceDef(){ }

            private:
                AbstractInterfaceDef( const AbstractInterfaceDef&) { }
                void operator=(const AbstractInterfaceDef&) { }
                ORB_ptr pORB;
        };  // class AbstractInterfaceDef



        class OBBEXPDLL AbstractInterfaceDef_out
         {
            public:
                AbstractInterfaceDef_out (AbstractInterfaceDef_ptr & p);
                AbstractInterfaceDef_out (AbstractInterfaceDef_var & p);
                AbstractInterfaceDef_out (const AbstractInterfaceDef_out & p) : ptr_(p.ptr_) {}
                AbstractInterfaceDef_out & operator=(const AbstractInterfaceDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                AbstractInterfaceDef_out & operator=(const AbstractInterfaceDef_var & a);
                AbstractInterfaceDef_out & operator=(AbstractInterfaceDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator AbstractInterfaceDef_ptr & () { return ptr_; }
                inline AbstractInterfaceDef_ptr & ptr () { return ptr_; }
                inline AbstractInterfaceDef_ptr operator->() { return ptr_; }
            private:
                AbstractInterfaceDef_ptr & ptr_;
        };  // class AbstractInterfaceDef_out



        static const TypeCode_ptr _tc_LocalInterfaceDef;
        class OBBEXPDLL LocalInterfaceDef : public virtual  InterfaceDef
         {
            public:
                static LocalInterfaceDef_ptr _duplicate(LocalInterfaceDef_ptr obj) 
                    {if (! is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static LocalInterfaceDef_ptr _narrow(Object_ptr obj, Boolean isa = CORBA_TRUE);
                inline static LocalInterfaceDef_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

            protected:
                LocalInterfaceDef(Object_ptr obj = 0);
                virtual ~LocalInterfaceDef(){ }

            private:
                LocalInterfaceDef( const LocalInterfaceDef&) { }
                void operator=(const LocalInterfaceDef&) { }
                ORB_ptr pORB;
        };  // class LocalInterfaceDef



        class OBBEXPDLL LocalInterfaceDef_out
         {
            public:
                LocalInterfaceDef_out (LocalInterfaceDef_ptr & p);
                LocalInterfaceDef_out (LocalInterfaceDef_var & p);
                LocalInterfaceDef_out (const LocalInterfaceDef_out & p) : ptr_(p.ptr_) {}
                LocalInterfaceDef_out & operator=(const LocalInterfaceDef_out & a) {
                    ptr_ = a.ptr_; return *this;}
                LocalInterfaceDef_out & operator=(const LocalInterfaceDef_var & a);
                LocalInterfaceDef_out & operator=(LocalInterfaceDef_ptr p) {
                ptr_ = p; return *this;}
                inline operator LocalInterfaceDef_ptr & () { return ptr_; }
                inline LocalInterfaceDef_ptr & ptr () { return ptr_; }
                inline LocalInterfaceDef_ptr operator->() { return ptr_; }
            private:
                LocalInterfaceDef_ptr & ptr_;
        };  // class LocalInterfaceDef_out


#ifdef ORB_IMPORT_DEFINED_ir_c
#undef ORB_IMPORT_DEFINED_ir_c
#undef OBBEXPDLL
#endif
#endif

