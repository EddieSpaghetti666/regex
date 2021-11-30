class State {
 public:
  enum Type { DEFAULT, SWITCH, MATCH };

  State(Type _type, const char _c, State* _out1, State* _out2)
      : type(_type), c(_c), out1(_out1), out2(_out2) {}

  Type type;
	char c;
  State* out1;
  State* out2;
};