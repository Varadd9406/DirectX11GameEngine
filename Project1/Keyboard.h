#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event()
			:
			type( Type::Invalid ),
			code( 0u )
		{}
		Event( Type type,unsigned char code )
			:
			type( type ),
			code( code )
		{}
		bool IsPress() const
		{
			return type == Type::Press;
		}
		bool IsRelease() const
		{
			return type == Type::Release;
		}
		bool IsValid() const
		{
			return type != Type::Invalid;
		}
		unsigned char GetCode() const
		{
			return code;
		}
	};
public:
	Keyboard() = default;
	Keyboard( const Keyboard& ) = delete;
	Keyboard& operator=( const Keyboard& ) = delete;
	// key event stuff
	bool KeyIsPressed( unsigned char keycode ) const;
	Event ReadKey();
	bool KeyIsEmpty() const;
	void FlushKey();
	// char event stuff
	char ReadChar();
	bool CharIsEmpty() const;
	void FlushChar();
	void Flush();
	// autorepeat control
	void EnableAutorepeat();
	void DisableAutorepeat();
	bool AutorepeatIsEnabled() const;
private:
	void OnKeyPressed( unsigned char keycode );
	void OnKeyReleased( unsigned char keycode );
	void OnChar( char character );
	void ClearState();
	template<typename T>
	static void TrimBuffer( std::queue<T>& buffer );
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;
};