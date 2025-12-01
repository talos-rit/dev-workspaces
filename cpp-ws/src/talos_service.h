#pragma once

#include <ostream>

#include "icd/v1/icd.grpc.pb.h"

namespace talos {
namespace icd {
namespace server {

class TalosOperatorService : public ::icd::v1::TalosOperatorService::Service {
public:
    explicit TalosOperatorService(std::ostream& out);
    ~TalosOperatorService() override;

private:
    std::ostream& out_;
};

} // namespace server
} // namespace icd
} // namespace talos
