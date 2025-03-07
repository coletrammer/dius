{ inputs, ... }:
{
  perSystem =
    { pkgs, system, ... }:
    let
      version = "0.1.0";
    in
    {
      packages = {
        default = pkgs.stdenv.mkDerivation {
          name = "dius-${version}";
          version = version;
          src = ../../.;

          buildInputs = with pkgs; [
            cmake
            inputs.di.packages.${system}.default
          ];
        };
        dius-runtime = pkgs.stdenv.mkDerivation {
          name = "dius-runtime-${version}";
          version = version;
          src = ../../.;

          cmakeFlags = [
            "-Ddius_USE_RUNTIME=ON"
          ];

          buildInputs = with pkgs; [
            cmake
            inputs.di.packages.${system}.default
          ];
        };
      };
    };
}
