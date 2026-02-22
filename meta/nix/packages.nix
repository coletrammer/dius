{ inputs, ... }:
{
  perSystem =
    { pkgs, system, ... }:
    let
      version = "0.1.0";

      mkPackage =
        stdenv: name: cmakeFlags:
        stdenv.mkDerivation {
          name = "${name}-${version}";
          version = version;
          src = ../../.;

          cmakeFlags = cmakeFlags;

          nativeBuildInputs = with pkgs; [
            cmake
            ninja
          ];

          propagatedBuildInputs = [
            inputs.di.packages.${system}.default
          ];
        };

      dius = mkPackage pkgs.stdenv "dius" [ ];
      dius-runtime = mkPackage pkgs.stdenv "dius-runtime" [ "-Ddius_USE_RUNTIME=ON" ];
      dius-static = mkPackage pkgs.pkgsStatic.stdenv "dius-static" [ ];
    in
    {
      packages = {
        default = dius;
        dius = dius;
        dius-runtime = dius-runtime;
        dius-static = dius-static;
      };
    };
}
