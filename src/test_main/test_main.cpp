#include "di/test/test_manager.h"
#include "dius/main.h"
#include "dius/sync_file.h"
#include "dius/system/process.h"

namespace dius::test {
static auto main(di::test::TestManager::Args& args) -> di::Result<void> {
    auto& manager = di::test::TestManager::the();

    manager.set_writer(di::ref(dius::stderr));
    manager.set_did_finish(dius::system::exit_process);

    return manager.run_tests(args);
}
}

DIUS_MAIN(di::test::TestManager::Args, dius::test)
