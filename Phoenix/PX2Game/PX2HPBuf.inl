/*
*
* �ļ�����	��	PX2HPBuf.inl
*
*/

//----------------------------------------------------------------------------
inline void HPBuf::SetMode (Mode mode)
{
	mMode = mode;
}
//----------------------------------------------------------------------------
inline HPBuf::Mode HPBuf::GetMode () const
{
	return mMode;
}
//----------------------------------------------------------------------------
inline void HPBuf::SetValue (float speed)
{
	mValue = speed;
}
//----------------------------------------------------------------------------
inline float HPBuf::GetValue () const
{
	return mValue;
}
//----------------------------------------------------------------------------