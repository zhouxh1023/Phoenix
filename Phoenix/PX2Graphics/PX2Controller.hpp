/*
*
* 文件名称	：	PX2Controller.hpp
*
*/

#ifndef PX2CONTROLLER_HPP
#define PX2CONTROLLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class Controller;
	typedef void (*CtrlPlayedCallback) (Controller *ctrl);

	class Controlledable;

	class Controller : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(Controller);

	protected:
		Controller ();
	public:
		virtual ~Controller ();

		// 优先级越高，越在前更新
		void SetPriority (int priority);
		int GetPriority () const;

		// 播放系统
		virtual void ResetPlay ();
		virtual void Play ();
		virtual bool IsPlaying () const;
		virtual void Stop ();
		virtual void Reset ();

		// 播放时间
		void SetMaxPlayTime (float time); // -1.0f forever
		float GetMaxPlayTime () const;
		void SetDelayPlayTime (float time);
		float GetDelayPlayTime () const;
		float GetPlayedTime () const;
		float GetPlayedTimeMinusDelay () const; // GetPlayedTime()-GetDelayPlayTime()

		// 播放控制
		void SetPlayedDoDetach(bool doDetach);
		bool IsPlayedDoDetach () const;
		void SetPlayedCallback (CtrlPlayedCallback callback);
		CtrlPlayedCallback GetPlayedCallback ();

		// 成员访问
		Controlledable* GetControlledable () const;
		double GetApplicationTime () const;

		// 动画更新，applicationTime是以毫秒作计算单位的
		virtual bool Update (double applicationTime);
		bool IsTimeInited ();
		float GetElapsedTime () const; //< 获得帧流逝时间，在Update调用后调用
		float GetRunTime () const;

		/// 动画更新类型
		enum RepeatType
		{
			RT_NONE,
			RT_CLAMP,
			RT_WRAP,
			RT_CYCLE
		};
		
		// 成员访问
		RepeatType Repeat;  //< default = RT_NONE
		double MinTime;     //< default = 0
		double MaxTime;     //< default = 0
		double Phase;       //< default = 0
		double Frequency;   //< default = 1
		bool Active;        //< default = true

		virtual void OnAttach ();
		virtual void OnDetach ();

public_internal:
		/// 设置被控制的对象
		virtual void SetControlledable (Controlledable* object);
		static bool LessThan (const Controller *ctrl0, const Controller *ctrl1);

	protected:
		/// 将应用程序的时间转换到控制器的当前时间。派生类在更新自己的时候会
		/// 用到此函数。
		double GetControlTimeByRangeTime (double rangeTime);
		virtual void _Update (double applicationTime);

		/// 使用一个常规指针指向被控制的对象。这样避免controller和mObject之间
		/// smart指针的循环依赖
		Controlledable* mObject;

		int mPriority;
		float mDelayPlayTime;
		float mMaxPlayTime;
		bool mIsPlayedDoDetach;
		bool mIsPlaying; // 不需要保存
		float mPlayedTime; // 不需要保存

		CtrlPlayedCallback mPlayedCallback;

		/// 以毫秒作单位的应用程序事件
		double mApplicationTime;
		double mLastApplicationTime;
		bool mIsTimeInited;
		double mInitedApplicationIime;
	};

	PX2_REGISTER_STREAM(Controller);
	typedef Pointer0<Controller> ControllerPtr;
#include "PX2Controller.inl"

}

#endif