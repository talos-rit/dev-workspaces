#include "talos_service.h"

#include <grpcpp/grpcpp.h>

namespace talos {
namespace icd {
namespace server {

TalosOperatorService::TalosOperatorService(std::ostream& out) : out_(out) {}

TalosOperatorService::~TalosOperatorService() = default;

::grpc::Status TalosOperatorService::Handshake(::grpc::ServerContext* /*context*/, const ::icd::v1::HandshakeRequest* /*request*/, ::icd::v1::HandshakeResponse* response) {
	response->mutable_status()->set_return_code(0);
	response->set_major_version(1);
	response->set_minor_version(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::PolarPanDiscrete(::grpc::ServerContext* /*context*/, const ::icd::v1::PolarPanDiscreteRequest* /*request*/, ::icd::v1::PolarPanDiscreteResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::Home(::grpc::ServerContext* /*context*/, const ::icd::v1::HomeRequest* /*request*/, ::icd::v1::HomeResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::PolarPanContinuousStart(::grpc::ServerContext* /*context*/, const ::icd::v1::PolarPanContinuousStartRequest* /*request*/, ::icd::v1::PolarPanContinuousStartResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::PolarPanContinuousStop(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::icd::v1::PolarPanContinuousStopResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::CartesianMoveDiscrete(::grpc::ServerContext* /*context*/, const ::icd::v1::CartesianMoveDiscreteRequest* /*request*/, ::icd::v1::CartesianMoveDiscreteResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::CartesianMoveContinuousStart(::grpc::ServerContext* /*context*/, const ::icd::v1::CartesianMoveContinuousStartRequest* /*request*/, ::icd::v1::CartesianMoveContinuousStartResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::CartesianMoveContinuousStop(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::icd::v1::CartesianMoveContinuousStopResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::ExecuteHardwareOperation(::grpc::ServerContext* /*context*/, const ::icd::v1::ExecuteHardwareOperationRequest* request, ::icd::v1::ExecuteHardwareOperationResponse* response) {
	response->mutable_status()->set_return_code(0);
	response->set_subcommand_id(request->subcommand_id());
	response->clear_payload();
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::GetSpeed(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::icd::v1::GetSpeedResponse* response) {
	response->mutable_status()->set_return_code(0);
	response->set_speed(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::SetSpeed(::grpc::ServerContext* /*context*/, const ::icd::v1::SetSpeedRequest* /*request*/, ::icd::v1::SetSpeedResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::SavePosition(::grpc::ServerContext* /*context*/, const ::icd::v1::SavePositionRequest* /*request*/, ::icd::v1::SavePositionResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::DeletePosition(::grpc::ServerContext* /*context*/, const ::icd::v1::DeletePositionRequest* /*request*/, ::icd::v1::DeletePositionResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::GoToPosition(::grpc::ServerContext* /*context*/, const ::icd::v1::GoToPositionRequest* /*request*/, ::icd::v1::GoToPositionResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::SetPolarPosition(::grpc::ServerContext* /*context*/, const ::icd::v1::SetPolarPositionRequest* /*request*/, ::icd::v1::SetPolarPositionResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::GetPolarPosition(::grpc::ServerContext* /*context*/, const ::icd::v1::GetPolarPositionRequest* /*request*/, ::icd::v1::GetPolarPositionResponse* response) {
	response->mutable_status()->set_return_code(0);
	response->set_delta_tenths_deg(0);
	response->set_azimuth_tenths_deg(0);
	response->set_radius_tenths(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::SetCartesianPosition(::grpc::ServerContext* /*context*/, const ::icd::v1::SetCartesianPositionRequest* /*request*/, ::icd::v1::SetCartesianPositionResponse* response) {
	response->mutable_status()->set_return_code(0);
	return ::grpc::Status::OK;
}

::grpc::Status TalosOperatorService::GetCartesianPosition(::grpc::ServerContext* /*context*/, const ::icd::v1::GetCartesianPositionRequest* /*request*/, ::icd::v1::GetCartesianPositionResponse* response) {
	response->mutable_status()->set_return_code(0);
	response->set_x_tenths_mm(0);
	response->set_y_tenths_mm(0);
	response->set_z_tenths_mm(0);
	return ::grpc::Status::OK;
}

} // namespace server
} // namespace icd
} // namespace talos
