class StateManager
{
public:
	static StateManager	*CreateInstance();
	static StateManager	*GetInstance() {return sInstance;};

	~StateManager(){};
	enum 
	{
		Title,
		InGame,
		GameOver
	};

	int32_t		GetState();
	void		SetState(int32_t stateToSet);
	void		Shutdown();
private:
	static StateManager *sInstance;
	StateManager(){};
	int32_t		mCurrentState;
};