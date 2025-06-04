
/***************************************************************************
 *   Copyright (C) 2005 by Matthew Adams                                   *
 *   roguestar191 at comcast dot net                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
// This code is based on the work of newty.de. Credit is due where it is due.
#ifdef FUNCTORS_INC
#else
#define FUNCTORS_INC 1
#include "tools.h"
#include <boost/shared_ptr.hpp>
class inet_player;
class TFunctor {
	public:
		Tools::Attributes attribs;
		bool sfunc;
		TFunctor(){ sfunc = false; }
		virtual ~TFunctor(){};
		virtual void *Call(std::vector<std::string>&d, int &sock_in, bool *isDown,boost::shared_ptr<inet_player>)=0;
		virtual std::string Call(std::vector<std::string> &d, void *caller,boost::shared_ptr<inet_player>)=0;
};

template <class T>
class TEFunctor {
	public:
		Tools::Attributes attribs;
		bool sfunc;
		TEFunctor(){ sfunc = false; }
		virtual ~TEFunctor(){};
		virtual void *Call(T&d, int &sock_in, bool *isDown, boost::shared_ptr<inet_player>)=0;
		
};
template <class TClass> class SFunctor : public TFunctor {
	std::string (TClass::*fpt1)();
	std::string (TClass::*fpt2)(std::vector<std::string>&);
	void (TClass::*fpt3)();
	void (TClass::*fpt4)(std::vector<std::string>&);
	void (TClass::*fpt5)(void *);
	void (TClass::*fpt6)(std::vector<std::string>&, void*);
	std::string (TClass::*fpt7)(std::vector<std::string> &, void*);
	std::string (TClass::*fpt8)(void*);
	std::string (TClass::*fpt9)(std::string&, void*);
	TClass *obj;
	public:
        virtual std::string Call(std::vector<std::string> &d, void *caller,boost::shared_ptr<inet_player> ){
			if(fpt1 != NULL) {
				return (*obj.*fpt1)();	
			} else if(fpt2 != NULL) {
				return (*obj.*fpt2)(d);
			} else if(fpt3 != NULL) {
				(*obj.*fpt3)();
			} else if(fpt4 != NULL) {
				(*obj.*fpt4)(d);
			} else if(fpt5 != NULL) {
				(*obj.*fpt5)(caller);
			} else if(fpt6 != NULL) {
				(*obj.*fpt6)(d, caller);
			} else if(fpt7 != NULL) {
				return (*obj.*fpt7)(d, caller);
			} else if(fpt8 != NULL) {
				return (*obj.*fpt8)(caller);
			} else if(fpt9 != NULL) {
                std::string a;
                unsigned int x;
                for(x = 0; x < d.size(); x++) {
                    a.append(d[x]);
                    a.append(" ");
                }
                return (*obj.*fpt9)(a, caller);
			}
			std::string x = "";
			return x;
		};//don't use this one.
        virtual void *Call(std::vector<std::string>&d, int &sock_in, bool *isDown,boost::shared_ptr<inet_player>) {
			return NULL;
		}
	void nullify() {
		sfunc = true;
		fpt1 = NULL;
		fpt2 = NULL;
		fpt3 = NULL;
		fpt4 = NULL;
		fpt5 = NULL;
		fpt6 = NULL;
		fpt7 = NULL;
		fpt8 = NULL;
		fpt9 = NULL;
	}
	SFunctor(TClass* _pt2Object, std::string(TClass::*_fpt)())
	{ nullify();obj = _pt2Object;  fpt1=_fpt;};
	SFunctor(TClass* _pt2Object, std::string(TClass::*_fpt)(std::vector<std::string>&))
	{ nullify();obj = _pt2Object;  fpt2=_fpt;};
	SFunctor(TClass* _pt2Object, void(TClass::*_fpt)())
	{ nullify();obj = _pt2Object;  fpt3=_fpt;};
	SFunctor(TClass* _pt2Object, void(TClass::*_fpt)(std::vector<std::string>&))
	{ nullify();obj = _pt2Object;  fpt4=_fpt;};

	SFunctor(TClass* _pt2Object, void(TClass::*_fpt)(void*))
	{ nullify();obj = _pt2Object;  fpt5=_fpt;};

	SFunctor(TClass* _pt2Object, void(TClass::*_fpt)(std::vector<std::string>&, void*))
	{ nullify();obj = _pt2Object;  fpt6=_fpt;};

	SFunctor(TClass* _pt2Object, std::string(TClass::*_fpt)(std::vector<std::string>&, void*))
	{ nullify();obj = _pt2Object;  fpt7=_fpt;};

	SFunctor(TClass* _pt2Object, std::string(TClass::*_fpt)(void*))
	{ nullify();obj = _pt2Object;  fpt8=_fpt;};

  SFunctor(TClass* _pt2Object, std::string(TClass::*_fpt)(std::string&,void*))
    { nullify();obj = _pt2Object;  fpt9=_fpt;};
};
template <class TClass> class Functor : public TFunctor 
{
	// To add a new callback method, add a new fpt type here,
	//set it to NULL in nullify, then add it to the list
	// of if/else in the main Call method.
	private:
		void (TClass::*fpt1)();
		void (TClass::*fpt2)(std::string &);
		void (TClass::*fpt3)(const char *);
		void (TClass::*fpt4)(const char *array[]);
		void (TClass::*fpt5)(const char *, const char *);
		void (TClass::*fpt6)(bool *);
		void (TClass::*fpt7)(int);
		void (TClass::*fpt8)(char);
		void (TClass::*fpt9)(std::vector<std::string *> *d);
		void (TClass::*fpt10)(std::vector<std::string *> *d, int &sock_in);
		void (TClass::*fpt11)(std::string &, int&);		
		void (TClass::*fpt12)(std::vector<std::string *> *, int &, bool);
		TClass* pt2Object; // pointer to object
        public:
		virtual std::string Call(std::vector<std::string> &d, void *caller,boost::shared_ptr<inet_player>){std::string x; return x;};//don't use this one.
		// New singularlized call method {{{:
		virtual void *Call(std::vector<std::string>&d, int &sock_in, bool *isDown,boost::shared_ptr<inet_player>) {
			//Comments {{{
			//ok, d[0] == command typed
			//    d[1] == arg1
			//    d[2] == arg2, etc. 
			//    sometimes socket can be ignored
			// }}}
			if(fpt1 != NULL) { // fpt1() no args {{{
				(*pt2Object.*fpt1)();
			// }}}
			} else if(fpt2 != NULL) { // fpt2(std::string &)  {{{
				std::string a;
				unsigned int x;
				for(x = 0; x < d.size(); x++) {
					a.append(d[x]);
					a.append(" ");
				}
				(*pt2Object.*fpt2)(a);
			// }}}
			} else if(fpt3 != NULL) { //fpt3(const char *); {{{
				if(d.size() >= 2) {
					(*pt2Object.*fpt3)(d[1].c_str());
				} else (*pt2Object.*fpt3)((const char *)NULL);
			// }}}
			} else if(fpt4 != NULL) { // (const char *array[]); {{{
				std::vector<const char *> buf;
				for(unsigned int c = 0; c < d.size(); ) {
					buf.push_back(d[c].c_str());
					c++;
					if( !(c < d.size() ) ) {
						buf.push_back(" ");
					}
				}
				(*pt2Object.*fpt4)(&buf[0]);
			// }}}
			} else if(fpt5 != NULL) { //(const char *, const char *); {{{
				if(d.size() <= 1) {
					(*pt2Object.*fpt5)((const char *)NULL, (const char *)NULL);
				} else if(d.size() <= 2) {
					(*pt2Object.*fpt5)(d[1].c_str(), (const char *)NULL);
				} else {
					(*pt2Object.*fpt5)(d[1].c_str(), d[2].c_str());
				} 
			//}}}
			} else if(fpt6 != NULL) { //(bool *); {{{
				(*pt2Object.*fpt6)(isDown);
			// }}}
			}else if(fpt7 != NULL) { // (int) {{{
				if(d.size() < 2) {
					(*pt2Object.*fpt7)(0);
				} else {
					(*pt2Object.*fpt7)(atoi(d[1].c_str()));
			
				}
			// }}}
			} else if(fpt8 != NULL) { // (char) {{{
				if(d.size() < 2) {
					char err = 0;
					(*pt2Object.*fpt8)(err);
				}  else { 
					(*pt2Object.*fpt8)(d[1][0]);
				} 
			// }}}
			} else if(fpt9 != NULL) { // (std::vector<std::string *> *d) {{{
				std::vector<std::string *> dup;
				std::vector<std::string>::iterator ptr = d.begin();
				while(ptr < d.end()) {
					dup.push_back(&(*(ptr)));
					ptr++;
				}
				(*pt2Object.*fpt9)(&dup);
			// }}}
			} else if(fpt10 != NULL) { // (std::vector<std::string *> *d, int) {{{
                std::vector<std::string *> dup;
				std::vector<std::string>::iterator ptr = d.begin();
                while(ptr < d.end()) {
                    dup.push_back(&(*(ptr)));
                    ptr++;
                }
                (*pt2Object.*fpt10)(&dup, sock_in);
			// }}}
			} else if(fpt11 != NULL) { //(std::string &, int&); {{{
				std::string a;
				unsigned int x;
				for(x = 0; x < d.size(); x++) {
					a.append(d[x]);
					a.append(" ");
				}
				(*pt2Object.*fpt11)(a, sock_in);
			// }}}
			} else if(fpt12 != NULL) { //(std::vector<std::string *> *, int &, bool); // {{{
				std::vector<std::string *> dup;
				std::vector<std::string>::iterator ptr = d.begin();
				while(ptr < d.end()) {
					dup.push_back(&(*(ptr)));
					ptr++;
				}
				(*pt2Object.*fpt12)(&dup, sock_in, false);
			} // }}}
			return &(attribs._return);
			return NULL;
		} // }}}
		void nullify() { // Set all the fpt's to null {{{
			sfunc = false;
			fpt1 = NULL;
			fpt2 = NULL;
			fpt3 = NULL;
			fpt4 = NULL;
			fpt5 = NULL;
			fpt6 = NULL;
			fpt7 = NULL;
			fpt8 = NULL;
			fpt9 = NULL;
			fpt10 = NULL;
			fpt11 = NULL;
			fpt12 = NULL;
		}; // Nullify }}}
		// Constructors, call nullify, set pt2object and function pointer {{{
		Functor(TClass* _pt2Object, void(TClass::*_fpt)())
		{ nullify();pt2Object = _pt2Object;  fpt1=_fpt;};
//1 std::string
		Functor(TClass* _pt2Object, void(TClass::*_fpt)(std::string &))
		{ nullify();pt2Object = _pt2Object;  fpt2=_fpt; };
//1 c string
		Functor(TClass* _pt2Object, void(TClass::*_fpt)(const char *))
		{ nullify();pt2Object = _pt2Object;  fpt3=_fpt;};
		Functor(TClass* _pt2Object, void(TClass::*_fpt)(const char *array[]))
		{ nullify();pt2Object = _pt2Object; fpt4=_fpt;};
//2 c strings
		Functor(TClass* _Obj, void(TClass::*_fpt)(const char *, const char *))
		{ nullify();pt2Object = _Obj; fpt5=_fpt; };
//1 bool
		Functor(TClass* _Obj, void(TClass::*_fpt)(bool *))
		{ nullify();pt2Object = _Obj; fpt6=_fpt; };

		Functor(TClass* _Obj, void(TClass::*_fpt)(int))
		{ nullify();pt2Object = _Obj; fpt7=_fpt; };


		Functor(TClass* _Obj, void(TClass::*_fpt)(char))
		{ nullify();pt2Object = _Obj; fpt8=_fpt; };

		Functor(TClass* _Obj, void(TClass::*_fpt)(std::vector<std::string *> *d))
		{ nullify();pt2Object = _Obj, fpt9=_fpt; };		

		Functor(TClass* _Obj, void(TClass::*_fpt)(std::vector<std::string *> *d, int &))
		{ nullify();pt2Object = _Obj, fpt10=_fpt; }

		Functor(TClass* _pt2Object, void(TClass::*_fpt)(std::string &, int&))
		{ nullify();pt2Object = _pt2Object;  fpt11=_fpt; };
		
		Functor(TClass* _Obj, void(TClass::*_fpt)(std::vector<std::string *> *d, int &, bool))
		{ nullify();pt2Object = _Obj, fpt12=_fpt; }
 // }}}

		virtual ~Functor(){};

// Old call methods {{{
/*
                virtual void Call()
                {
                        (*pt2Object.*fpt1)();
                };
                virtual void Call(std::string &string)
                {
                        (*pt2Object.*fpt2)(string);
                };  // execute member function

               virtual void Call(const char *string)
                {
                        (*pt2Object.*fpt3)(string);
                };
                virtual void Call(const char *string[])
                {
                        (*pt2Object.*fpt4)(string);
                };
                virtual void Call(const char *s1, const char *s2)
                {
                        (*pt2Object.*fpt5)(s1, s2);
                };
                virtual void Call(bool *b1)
                {
                        (*pt2Object.*fpt6)(b1);
                };
                virtual void Call(int b1)
                {
                        (*pt2Object.*fpt7)(b1);
                };

                virtual void Call(char b1)
                {
                        (*pt2Object.*fpt8)(b1);
                };
		virtual void Call(std::vector<std::string *> *d)
		{
			(*pt2Object.*fpt9)(d);
		}

                virtual void Call(std::vector<std::string *> *d, int &sock_in)
                {
			if(fpt10 != NULL) 
                        (*pt2Object.*fpt10)(d, sock_in);
			else
			(*pt2Object.*fpt12)(d, sock_in, false);
                }
                virtual void Call(std::string &string, int &sock_in)
                {
                        (*pt2Object.*fpt11)(string, sock_in);
                };  // execute member function

 }}} */


};
template <class TClass> class VecFunctor : public TFunctor 
{
	// To add a new callback method, add a new fpt type here,
	//set it to NULL in nullify, then add it to the list
	// of if/else in the main Call method.
	private:
		void (TClass::*fpt)(std::vector<std::string> &d);
		TClass* pt2Object; // pointer to object
        public:
		virtual std::string Call(std::vector<std::string> &d, void *caller,boost::shared_ptr<inet_player>){std::string x; return x;};//don't use this one.
		// New singularlized call method {{{:
		virtual void *Call(std::vector<std::string>&d, int &sock_in, bool *isDown,boost::shared_ptr<inet_player>) {
			//Comments 
			//ok, d[0] == command typed
			//    d[1] == arg1
			//    d[2] == arg2, etc.
			//    sometimes socket can be ignored
				if(fpt!= NULL)  (*pt2Object.*fpt)(d);
				return &(attribs._return);
				return NULL;
		}
		VecFunctor(TClass* _Obj, void(TClass::*_fpt)(std::vector<std::string> &d))
		{ pt2Object = _Obj, fpt=_fpt; };		
		virtual ~VecFunctor(){};
};
class VecFunctorNoClass : public TFunctor 
{
	// To add a new callback method, add a new fpt type here,
	//set it to NULL in nullify, then add it to the list
	// of if/else in the main Call method.
	private:
		void (*fpt)(std::vector<std::string> &d);
		//TClass* pt2Object; // pointer to object
        public:
		virtual std::string Call(std::vector<std::string> &d, void *caller,boost::shared_ptr<inet_player>){std::string x; return x;};//don't use this one.
		// New singularlized call method {{{:
		virtual void *Call(std::vector<std::string>&d, int &sock_in, bool *isDown,boost::shared_ptr<inet_player>) {
			//Comments 
			//ok, d[0] == command typed
			//    d[1] == arg1
			//    d[2] == arg2, etc.
			//    sometimes socket can be ignored
				if(fpt!= NULL)  (*fpt)(d);
				return &(attribs._return);
				return NULL;
		}
		VecFunctorNoClass( void(*_fpt)(std::vector<std::string> &d))
		{  fpt=_fpt; };		
		virtual ~VecFunctorNoClass(){};
};
template <class TClass> class VoidFunctor : public TFunctor 
{
	// To add a new callback method, add a new fpt type here,
	//set it to NULL in nullify, then add it to the list
	// of if/else in the main Call method.
	private:
		void (TClass::*fpt)(void);
		TClass* pt2Object; // pointer to object
        public:
		virtual std::string Call(std::vector<std::string> &d, void *caller,boost::shared_ptr<inet_player>){std::string x; return x;};//don't use this one.
		// New singularlized call method {{{:
		virtual void *Call(std::vector<std::string>&d, int &sock_in, bool *isDown,boost::shared_ptr<inet_player>s) {
			//Comments 
			//ok, d[0] == command typed
			//    d[1] == arg1
			//    d[2] == arg2, etc.
			//    sometimes socket can be ignored
			//std::cout << "calling voidfunctor function pointer.\n";
				if(fpt!= NULL)  (*pt2Object.*fpt)();
				return &(attribs._return);
				return NULL;
		}
		VoidFunctor(TClass* _Obj, void(TClass::*_fpt)(void))
		{ pt2Object = _Obj, fpt=_fpt; };		
		virtual ~VoidFunctor(){};
};
template <class TClass, class Arg> class TemplateFunctor : public TEFunctor<Arg>
{
	// To add a new callback method, add a new fpt type here,
	//set it to NULL in nullify, then add it to the list
	// of if/else in the main Call method.
	private:
		void (TClass::*fpt)(Arg);
		TClass* pt2Object; // pointer to object
        public:
		virtual std::string Call(std::vector<std::string> &d, void *caller,boost::shared_ptr<inet_player>){std::string x; return x;};//don't use this one.
		// New singularlized call method {{{:
		virtual void *Call(Arg &d, int &sock_in, bool *isDown,boost::shared_ptr<inet_player>) {
			//Comments 
			//ok, d[0] == command typed
			//    d[1] == arg1
			//    d[2] == arg2, etc.
			//    sometimes socket can be ignored
				if(fpt!= NULL)  (*pt2Object.*fpt)(d);
				return &(TEFunctor<Arg>::attribs._return);
				return NULL;
		}
		TemplateFunctor(TClass* _Obj, void(TClass::*_fpt)(Arg))
		{ pt2Object = _Obj, fpt=_fpt; };		
		virtual ~TemplateFunctor(){};
};

// For allowing easier server creation..
#ifdef IS_A_SERVER
class server_functor_base {
	public:
		server_functor_base(){ }
		virtual ~server_functor_base(){};
		virtual void Call(unsigned int,std::string&,fd_set&)=0;
		virtual void Call(unsigned int)=0;
};
template <class TClass> class ServerFunctor : public server_functor_base {
	void (TClass::*fpt1)(unsigned int);
	void (TClass::*fpt2)(unsigned int,std::string&,fd_set&);
	TClass *obj;
	public:
        virtual void Call(unsigned int a, std::string &b,fd_set &m ){
		(*obj.*fpt2)(a,b,m);
		return;
	}
	virtual void Call(unsigned int a) {
		(*obj.*fpt1)(a);
		return;
	}
        void nullify() {
		fpt1 = NULL;
		fpt2 = NULL;
	}
	ServerFunctor(TClass* _pt2Object, void(TClass::*_fpt)(unsigned int))
	{ nullify();obj = _pt2Object;  fpt1=_fpt;};
	ServerFunctor(TClass* _pt2Object, void(TClass::*_fpt)(unsigned int,std::string&,fd_set&))
	{ nullify();obj = _pt2Object;  fpt2=_fpt;};

};
#endif

#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */

