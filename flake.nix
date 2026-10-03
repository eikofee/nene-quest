{
  description = "Nene Quest - a 2D side-scrolling game written in C++ with SFML";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        # The code uses the SFML 2.x API (SFML 3 has breaking changes)
        sfml = pkgs.sfml_2;
      in
      {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "nenequest";
          version = "0.1.0";
          src = ./nenequest;

          nativeBuildInputs = [ pkgs.cmake pkgs.makeWrapper ];
          buildInputs = [ sfml ];

          # The game loads assets with paths relative to the working
          # directory (e.g. "img/player1.png"), so install them next to the
          # binary and wrap it to run from there.
          installPhase = ''
            runHook preInstall
            mkdir -p $out/share/nenequest $out/bin
            cp NeneQuest $out/share/nenequest/
            cp -r ../img ../fonts ../bgm ../sfx ../levels ../config $out/share/nenequest/
            makeWrapper $out/share/nenequest/NeneQuest $out/bin/nenequest \
              --chdir $out/share/nenequest
            runHook postInstall
          '';
        };

        apps.default = {
          type = "app";
          program = "${self.packages.${system}.default}/bin/nenequest";
        };

        devShells.default = pkgs.mkShell {
          inputsFrom = [ self.packages.${system}.default ];
          packages = [ pkgs.gdb pkgs.clang-tools ];
        };
      });
}
