{ inputs, ... }:
{
  perSystem =
    {
      config,
      pkgs,
      system,
      ...
    }:
    let
      constants = import ../constants.nix { inherit system; };
      gcc = pkgs."gcc${constants.gccVersion}";
      clang = pkgs."llvmPackages_${constants.clangVersion}".libcxxClang;
      stdenv = pkgs."gcc${constants.gccVersion}Stdenv";
    in
    {
      devShells.default = pkgs.mkShell.override { inherit stdenv; } {
        shellHook = ''
          export DIUS_DOXYGEN_AWESOME_DIR=${inputs.doxygen-awesome-css};
          export DIUS_UNICODE_DATABASE_DIR=${pkgs.unicode-character-database}/share/unicode
          export DIUS_UNICODE_EMOJI_DATABASE_DIR=${pkgs.unicode-emoji}/share/unicode/emoji
        '';
        packages =
          [
            # Compilers
            clang
            gcc
          ]
          # Treefmt and all individual formatters
          ++ [ config.treefmt.build.wrapper ]
          ++ builtins.attrValues config.treefmt.build.programs
          ++ (with pkgs; [
            # Build support
            cmake
            ninja
            ccache

            # justfile support
            just
            jq
            fzf

            # python for parsing Unicode database and generating source files
            python3

            # Docs
            doxygen
            graphviz

            # Coverage
            lcov

            # Dependencies
            inputs.di.packages.${system}.default
          ]);
      };
    };
}
