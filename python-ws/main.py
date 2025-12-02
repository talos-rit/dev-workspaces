"""Simple gRPC client that exercises all TalosOperator RPCs."""

from __future__ import annotations

import argparse
from typing import Callable, Iterable

import grpc
import src.proto.icd.v1.icd_pb2 as icd_pb2
import src.proto.icd.v1.icd_pb2_grpc as icd_pb2_grpc
from google.protobuf import empty_pb2


def build_calls(
    stub: icd_pb2_grpc.TalosOperatorServiceStub,
) -> Iterable[tuple[str, Callable[[], object]]]:
    """Return callables that invoke every RPC once with sample data."""

    return [
        (
            "Handshake",
            lambda: stub.Handshake(icd_pb2.HandshakeRequest(operator_id=42)),
        ),
        (
            "PolarPanDiscrete",
            lambda: stub.PolarPanDiscrete(
                icd_pb2.PolarPanDiscreteRequest(
                    delta_azimuth_tenths_deg=150,
                    delta_altitude_tenths_deg=-75,
                    delay_ms=100,
                    execution_time_ms=500,
                )
            ),
        ),
        ("Home", lambda: stub.Home(icd_pb2.HomeRequest(delay_ms=0))),
        (
            "PolarPanContinuousStart",
            lambda: stub.PolarPanContinuousStart(
                icd_pb2.PolarPanContinuousStartRequest(
                    moving_azimuth=1,
                    moving_altitude=0,
                )
            ),
        ),
        (
            "PolarPanContinuousStop",
            lambda: stub.PolarPanContinuousStop(empty_pb2.Empty()),
        ),
        (
            "CartesianMoveDiscrete",
            lambda: stub.CartesianMoveDiscrete(
                icd_pb2.CartesianMoveDiscreteRequest(
                    delta_x_tenths_mm=100,
                    delta_y_tenths_mm=-50,
                    delta_z_tenths_mm=25,
                    delay_ms=200,
                    execution_time_ms=800,
                )
            ),
        ),
        (
            "CartesianMoveContinuousStart",
            lambda: stub.CartesianMoveContinuousStart(
                icd_pb2.CartesianMoveContinuousStartRequest(
                    moving_x=1,
                    moving_y=0,
                    moving_z=-1,
                )
            ),
        ),
        (
            "CartesianMoveContinuousStop",
            lambda: stub.CartesianMoveContinuousStop(empty_pb2.Empty()),
        ),
        (
            "ExecuteHardwareOperation",
            lambda: stub.ExecuteHardwareOperation(
                icd_pb2.ExecuteHardwareOperationRequest(
                    subcommand_id=7,
                    payload=b"\x01\x02",
                )
            ),
        ),
        ("GetSpeed", lambda: stub.GetSpeed(empty_pb2.Empty())),
        ("SetSpeed", lambda: stub.SetSpeed(icd_pb2.SetSpeedRequest(speed=5))),
        (
            "SavePosition",
            lambda: stub.SavePosition(
                icd_pb2.SavePositionRequest(
                    name="demo",
                    anchor=True,
                    parent_reference="root",
                )
            ),
        ),
        (
            "DeletePosition",
            lambda: stub.DeletePosition(
                icd_pb2.DeletePositionRequest(name="obsolete"),
            ),
        ),
        (
            "GoToPosition",
            lambda: stub.GoToPosition(
                icd_pb2.GoToPositionRequest(name="demo"),
            ),
        ),
        (
            "SetPolarPosition",
            lambda: stub.SetPolarPosition(
                icd_pb2.SetPolarPositionRequest(
                    name="polar-demo",
                    delta_tenths_deg=90,
                    azimuth_tenths_deg=45,
                    radius_tenths=120,
                )
            ),
        ),
        (
            "GetPolarPosition",
            lambda: stub.GetPolarPosition(
                icd_pb2.GetPolarPositionRequest(name="polar-demo"),
            ),
        ),
        (
            "SetCartesianPosition",
            lambda: stub.SetCartesianPosition(
                icd_pb2.SetCartesianPositionRequest(
                    name="cart-demo",
                    x_tenths_mm=10,
                    y_tenths_mm=20,
                    z_tenths_mm=30,
                )
            ),
        ),
        (
            "GetCartesianPosition",
            lambda: stub.GetCartesianPosition(
                icd_pb2.GetCartesianPositionRequest(name="cart-demo"),
            ),
        ),
    ]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Call all TalosOperator RPCs using sample payloads.",
    )
    parser.add_argument(
        "--target",
        default="localhost:50051",
        help="gRPC target to connect to (host:port).",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    with grpc.insecure_channel(args.target) as channel:
        stub = icd_pb2_grpc.TalosOperatorServiceStub(channel)

        for name, caller in build_calls(stub):
            try:
                response = caller()
                print(f"{name}: {response}")
            except grpc.RpcError as err:
                print(
                    f"{name}: RPC error {err.code().name} - {err.details()}",
                )


if __name__ == "__main__":
    main()
