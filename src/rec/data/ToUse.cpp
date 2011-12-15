#if 0
namespace {

// TODO: move these to the main thread area.

static const int THREAD_SHUTDOWN_TIME = 10000;

struct ThreadDesc {
  int priority_;
  int period_;
  const char* name_;
};

ThreadDesc updateDesc = {5, 40, "Data::Update"};
ThreadDesc writeDesc = {5, 100, "Data::Write"};

template <typename Method>
Thread* makeLoop(const ThreadDesc& d, DataUpdater* upd, Method method) {
  thread_ptr<Thread> t(thread::makeLoop(d.period_, d.name_, upd, method));

  t->setPriority(d.priority_);
  t->startThread();

  return t.transfer();
}

}  // namespace

DataUpdater::~DataUpdater() {
  writeThread_->stopThread(THREAD_SHUTDOWN_TIME);
  updateThread_->stopThread(THREAD_SHUTDOWN_TIME);
  stl::deleteMapPointers(&map_);
}

void DataUpdater::start(DefaultRegistry* r, DataRegistry* dr) {
  CHECK(!instance_);
  instance_ = new DataUpdater(r, dr);
}

void DataUpdater::stop() {
  delete instance_;
  instance_ = NULL;
}

DataUpdater* DataUpdater::instance_ = NULL;

const DefaultRegistry& defaultRegistry() {
  return DataUpdater::instance()->defaultRegistry();
}

#endif


#if 0
void UndoStack::start() {
  running_ = true;
}

void UndoStack::stop() {
  running_ = false;
}

void UndoStack::dump(const string& name) const {
  DLOG(INFO) << name;
  for (uint i = 0; i < queue_.size(); ++i) {
    bool isCurrent = (i == (queue_.size() - undoes_ - 1));
    std::cerr << (isCurrent ? " --> " : "     ")
              << queue_[i]->ShortDebugString()
              << "\n";
  }
}

  void start();
  void stop();

  void dump(const string&) const;

  bool running_;


template <typename Proto>
void set(const Proto& p, const VirtualFile& f = file::none(),
         bool undoable = true) {
  editable<Proto>(f)->setValue(p, Address::default_instance(), undoable);
}

template <typename Proto>
void setValue(const Proto& p, const VirtualFile& f, const Address& a, bool undoable) {
  editable<Proto>(f)->setValue(p, a, undoable);
}

template <typename Proto>
const Proto get(const VirtualFile& f = file::none()) {
  return editable<Proto>(f)->get();
}

template <typename Proto>
const Value getValue(const Address& address, const VirtualFile& f) {
  return editable<Proto>(f)->getValue(address);
}

template <typename Proto>
void apply(const VirtualFile& vf, void (*op)(Proto*)) {
  Proto p(get<Proto>(vf));
  op(&p);
  set(p, vf);
}

template <typename Proto, typename Value>
void apply(const VirtualFile& vf, void (*op)(Proto*, Value), Value v) {
  Proto p(get<Proto>(vf));
  op(&p, v);
  set(p, vf);
}

template <typename Proto, typename V1, typename V2>
void apply(const VirtualFile& vf, void (*op)(Proto*, V1, V2), V1 v1, V2 v2) {
  Proto p(get<Proto>(vf));
  op(&p, v1, v2);
  set(p, vf);
}

template <typename Proto, typename Operator>
void apply(const VirtualFile& vf, Operator op) {
  Proto p(get<Proto>(vf));
  op(&p);
  set(p, vf);
}

template <typename Proto, typename Operator, typename Value>
void apply(const VirtualFile& vf, Operator op, Value v) {
  Proto p(get<Proto>(vf));
  op(&p, v);
  set(p, vf);
}

template <typename Proto, typename Operator, typename V1, typename V2>
void apply(const VirtualFile& vf, Operator op, V1 v1, V2 v2) {
  Proto p(get<Proto>(vf));
  op(&p, v1, v2);
  set(p, vf);
}

#endif

