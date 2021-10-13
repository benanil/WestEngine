//=============================================================================
// 
// (C) Copyright 2015 Amer Saffo (amer_saffo@yahoo.com)
// Distributed under the Code Project Open License 1.02 (CPOL)
// http://www.codeproject.com/info/cpol10.aspx
// 
//=============================================================================

//=============================================================================
// version 1.1
//=============================================================================

#ifndef SHARP_EVENT_HEADER__
#define SHARP_EVENT_HEADER__

//-----------------------------------------------------------------------------
// define SHARP_EVENT_NO_BOOST to have no dependencies and manage thread-safety
// at the application level. Boost is used ONLY to make this class thread-safe.
//-----------------------------------------------------------------------------
#define SHARP_EVENT_NO_BOOST
#ifndef SHARP_EVENT_NO_BOOST
#include "boost/thread/locks.hpp"
#include "boost/thread/shared_mutex.hpp"
#endif // SHARP_EVENT_NO_BOOST

#include <iostream>
#include <list>
#include <utility>  // for std::pair

namespace Sharp    // short for SharpTools
{
	template<typename T> class EventHandlerImplBase
	{
	public:
		EventHandlerImplBase() {}  ///< needed to define the constructor since we defined the destructor (compiler would otherwise object)
		virtual ~EventHandlerImplBase() {} ///< destructor should be made virtual for base as we are going to delete through a base pointer
		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>*) = 0;   ///< verify if both handlers are binded to the same function.

		/** convenient function to make inheriting classes implementation of IsBindedToSameFunctionAs a little bit easier*/
		bool IsSametype(EventHandlerImplBase<T>* pHandler2)
		{
			if (!pHandler2 ||  // a null pointer can never be the same as one that points to an actual handler
				typeid(*this) != typeid(*pHandler2))
			{
				return false;
			}

			return true;
		}
	};

	template<typename T>
	class EventHandlerImpl : public EventHandlerImplBase<T>
	{
	public:
		virtual void OnEvent(T&) = 0;  ///< will be called eventually when a Event is raised
	};

	template<typename T>
	class EventHandlerImplForNonMemberFunction : public EventHandlerImpl<T>
	{
	public:
		EventHandlerImplForNonMemberFunction(void(*functionToCall)(T&))
			: m_pFunctionToCall(functionToCall)
		{
		}

		virtual void OnEvent(T& evt)
		{
			m_pFunctionToCall(evt);
		}

		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>* pHandler2)
		{
			if (!IsSametype(pHandler2))
			{
				return false;
			}

			EventHandlerImplForNonMemberFunction<T>* pHandlerCasted = dynamic_cast<EventHandlerImplForNonMemberFunction<T>*>(pHandler2);
			if (!pHandlerCasted)
			{
				// error, should never happen
				return false;
			}

			return this->m_pFunctionToCall == pHandlerCasted->m_pFunctionToCall;
		}

	private:
		void(*m_pFunctionToCall)(T&); ///< passed in the constructor. Will get called when an event is raised.
	};

	template<typename T, typename U>
	class EventHandlerImplForMemberFunction : public EventHandlerImpl<T>
	{
	public:
		EventHandlerImplForMemberFunction(void(U::* memberFunctionToCall)(T&), U* thisPtr)
			: m_pCallerInstance(thisPtr)
			, m_pMemberFunction(memberFunctionToCall)
		{
		}

		virtual void OnEvent(T& evt)
		{
			if (m_pCallerInstance)
			{
				(m_pCallerInstance->*m_pMemberFunction)(evt);
			}
		}

		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>* pHandler2)
		{
			if (!IsSametype(pHandler2))
			{
				return false;
			}

			EventHandlerImplForMemberFunction<T, U>* pHandlerCasted = dynamic_cast<EventHandlerImplForMemberFunction<T, U>*>(pHandler2);
			if (!pHandlerCasted)
			{
				// error, should never happen
				return false;
			}

			return this->m_pCallerInstance == pHandlerCasted->m_pCallerInstance && this->m_pMemberFunction == pHandlerCasted->m_pMemberFunction;
		}

	private:
		U* m_pCallerInstance;  ///< passed in the constructor. This watcher will only be used to call a member function, so m_pCallerInstance would hold the object through which that member function is called.
		void(U::* m_pMemberFunction)(T&); ///< passed in the constructor. This watcher will only be used to call a member function through m_pCallerInstance.
	};

	template<>
	class EventHandlerImpl<void> : public EventHandlerImplBase<void>
	{
	public:
		virtual void OnEvent() = 0;  ///< will be called eventually when an Event is raised
	};

	template<>
	class EventHandlerImplForNonMemberFunction<void> : public EventHandlerImpl<void>
	{
	public:
		EventHandlerImplForNonMemberFunction(void(*functionToCall)())
			: m_pFunctionToCall(functionToCall)
		{
		}

		virtual void OnEvent()
		{
			m_pFunctionToCall();
		}

		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<void>* pHandler2)
		{
			if (!IsSametype(pHandler2))
			{
				return false;
			}

			EventHandlerImplForNonMemberFunction<void>* pHandlerCasted = dynamic_cast<EventHandlerImplForNonMemberFunction<void>*>(pHandler2);
			if (!pHandlerCasted)
			{
				// error, should never happen
				return false;
			}

			return this->m_pFunctionToCall == pHandlerCasted->m_pFunctionToCall;
		}

	private:
		void(*m_pFunctionToCall)(); ///< passed in the constructor. Will get called when an event is raised.
	};

	template<typename U>
	class EventHandlerImplForMemberFunction<void, U> : public EventHandlerImpl<void>
	{
	public:
		EventHandlerImplForMemberFunction(void(U::* memberFunctionToCall)(), U* thisPtr)
			: m_pCallerInstance(thisPtr)
			, m_pMemberFunction(memberFunctionToCall)
		{
		}

		virtual void OnEvent()
		{
			if (m_pCallerInstance)
			{
				(m_pCallerInstance->*m_pMemberFunction)();
			}
		}

		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<void>* pHandler2)
		{
			if (!IsSametype(pHandler2))
			{
				return false;
			}

			EventHandlerImplForMemberFunction<void, U>* pHandlerCasted = dynamic_cast<EventHandlerImplForMemberFunction<void, U>*>(pHandler2);
			if (!pHandlerCasted)
			{
				// error, should never happen
				return false;
			}

			return this->m_pCallerInstance == pHandlerCasted->m_pCallerInstance && this->m_pMemberFunction == pHandlerCasted->m_pMemberFunction;
		}

	private:
		U* m_pCallerInstance;  ///< passed in the constructor. This watcher will only be used to call a member function, so m_pCallerInstance would hold the object through which that member function is called.
		void(U::* m_pMemberFunction)(); ///< passed in the constructor. This watcher will only be used to call a member function through m_pCallerInstance.
	};

	class EventHandler
	{
	public:
		template<typename T>
		static EventHandlerImpl<T>* Bind(void(*nonMemberFunctionToCall)(T&))
		{
			return new EventHandlerImplForNonMemberFunction<T>(nonMemberFunctionToCall);
		}

		template<typename T, typename U>
		static EventHandlerImpl<T>* Bind(void(U::* memberFunctionToCall)(T&), U* thisPtr)
		{
			return new EventHandlerImplForMemberFunction<T, U>(memberFunctionToCall, thisPtr);
		}

		static EventHandlerImpl<void>* Bind(void(*nonMemberFunctionToCall)())
		{
			return new EventHandlerImplForNonMemberFunction<void>(nonMemberFunctionToCall);
		}

		template<typename U>
		static EventHandlerImpl<void>* Bind(void(U::* memberFunctionToCall)(), U* thisPtr)
		{
			return new EventHandlerImplForMemberFunction<void, U>(memberFunctionToCall, thisPtr);
		}

	private:
		EventHandler();  ///< default constructor made private to prevent creating instances of this class. EventHandler only purpose is to provide Event with the Bind function
	};

	template<typename T>
	class EventBase
	{
	public:
		EventBase() {}

		virtual ~EventBase()
		{
			//for (int i = 0; i < m_eventHandlers.size(); i++)
			//{
			//	EventHandlerImpl<T>* pHandler = &m_eventHandlers[i];
			//	if (pHandler)
			//	{
			//		delete pHandler;
			//		pHandler = 0;  // just to be consistent
			//	}
			//}
			//m_eventHandlers.clear();
		}

		EventBase<T>& operator += (EventHandlerImpl<T>* pHandlerToAdd)
		{
			if (pHandlerToAdd) {
				m_eventHandlers.push_back(pHandlerToAdd);
			}
			return *this;
		}

		EventBase<T>& operator -= (EventHandlerImpl<T>* pHandlerToRemove)
		{
			if (!pHandlerToRemove) {
				return *this;  // a null passed, so nothing to do
			}

			for (int i = 0; i < m_eventHandlers.size(); i++)
			{
				EventHandlerImpl<T>* pHandler = m_eventHandlers[i];
				if (pHandlerToRemove->IsBindedToSameFunctionAs(pHandler))
				{
					EventHandlerImpl<T>* pFoundHandler = m_eventHandlers[i];
					if (pFoundHandler) {
						delete pFoundHandler;
						pFoundHandler = 0;
					}
					m_eventHandlers.erase(i);
					break;
				}
			}

			if (pHandlerToRemove) {
				delete pHandlerToRemove;
				pHandlerToRemove = 0;
			}

			return *this;
		}

	private:
		EventBase(const EventBase&);  ///< private to disable copying
		EventBase& operator=(const EventBase&); ///< private to disable copying

	protected:
		std::list< EventHandlerImpl<T>* > m_eventHandlers;  ///< all handlers will be notified when operator() is called.
	};

	template<typename T> class Event : public EventBase<T>
	{
	public:
		void operator()(T& eventData)
		{

			//for (int i = 0; i < m_eventHandlers.size(); i++)
			//{
			//	EventHandlerImpl<T>* pHandler = m_eventHandlers[i];
			//	if (pHandler)
			//	{
			//		pHandler->OnEvent(eventData);  // this is a virtual function that will eventually call the function passed to Eventhandler::Bind() for this handler
			//	}
			//}
		}
	};

	template<> class Event<void> : public EventBase<void>
	{
	public:
		void operator()()
		{
			for (std::list< EventHandlerImpl<void>* >::iterator iter = m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<void>* pHandler = *iter;
				if (pHandler)
				{
					pHandler->OnEvent();  // this is a virtual function that will eventually call the function passed to Eventhandler::Bind() for this handler
				}
			}
		}
	};
}

#endif // SHARP_EVENT_HEADER__