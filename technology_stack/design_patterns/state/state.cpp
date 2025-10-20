#include <iostream>
#include <typeinfo>
#include <string>
#include <utility>

struct transition_t;

/**
 * @brief Represents a state in the state machine.
 * @note 4个基础的state：unconfigured,Inactive,Active,Finalized
 * @note 也有6个transition state: Configuring, Cleaningup, Shuttingdown, Activating, Deactivating, Errorprocessing
 * 
 */
struct state_t{
  std::string label;
  unsigned int id;
  transition_t* valid_transitions;
  unsigned int valid_transition_size;
};

/**
 * @brief Represents a transition between states in the state machine.
 * @note 7个基础的transition：create,configure,cleanup,activate,deactivate,shutdown,destroy
 */
struct transition_t {
  std::string label;
  unsigned int id;
  state_t* start_state;
  state_t* goal_state;
};

struct transition_map_t {
  state_t* start_state;
  unsigned int states_size;
  transition_t* transitions;
  unsigned int transitions_size;
};

struct state_machine_t {
  const state_t* current_state;
};

class State {
public:
  State(int id, std::string label) {
    reset();

    state_habdle.id = id;
    state_habdle.label = std::move(label);
  }
  State():State(0,""){}

  State(const State &other) {
    state_habdle = other.state_habdle;
  }

  State& operator=(const State &other) {
    if (this != &other) {
      state_habdle = other.state_habdle;
    }
    return *this;
  }

  virtual ~State() {
    reset();
  }

  void reset(){
    state_habdle.id = 0;
    state_habdle.label = "";
    state_habdle.valid_transitions = nullptr;
    state_habdle.valid_transition_size = 0;
  }

  int id() const { return state_habdle.id; }
  std::string label() const { return state_habdle.label; }

private:
  state_t state_habdle;
};

// /**
//  * The Context defines the interface of interest to clients. It also maintains a
//  * reference to an instance of a State subclass, which represents the current
//  * state of the Context.
//  */
// class Context {
//   /**
//    * @var State A reference to the current state of the Context.
//    */
//  private:
//   State *state_;

//  public:
//   Context(State *state) : state_(nullptr) {
//     this->TransitionTo(state);
//   }
//   ~Context() {
//     delete state_;
//   }
//   /**
//    * The Context allows changing the State object at runtime.
//    */
//   void TransitionTo(State *state) {
//     std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
//     if (this->state_ != nullptr)
//       delete this->state_;
//     this->state_ = state;
//     this->state_->set_context(this);
//   }
//   /**
//    * The Context delegates part of its behavior to the current State object.
//    */
//   void Request1() {
//     this->state_->Handle1();
//   }
//   void Request2() {
//     this->state_->Handle2();
//   }
// };

// /**
//  * Concrete States implement various behaviors, associated with a state of the
//  * Context.
//  */

// class ConcreteStateA : public State {
//  public:
//   void Handle1() override;

//   void Handle2() override {
//     std::cout << "ConcreteStateA handles request2.\n";
//   }
// };

// class ConcreteStateB : public State {
//  public:
//   void Handle1() override {
//     std::cout << "ConcreteStateB handles request1.\n";
//   }
//   void Handle2() override {
//     std::cout << "ConcreteStateB handles request2.\n";
//     std::cout << "ConcreteStateB wants to change the state of the context.\n";
//     this->context_->TransitionTo(new ConcreteStateA);
//   }
// };

// void ConcreteStateA::Handle1() {
//   {
//     std::cout << "ConcreteStateA handles request1.\n";
//     std::cout << "ConcreteStateA wants to change the state of the context.\n";

//     this->context_->TransitionTo(new ConcreteStateB);
//   }
// }

// /**
//  * The client code.
//  */
// void ClientCode() {
//   Context *context = new Context(new ConcreteStateA);
//   context->Request1();
//   context->Request2();
//   delete context;
// }

int main() {
  // ClientCode();
  return 0;
}