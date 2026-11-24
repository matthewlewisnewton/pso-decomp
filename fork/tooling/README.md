# Fork tooling workspace

The layered fork adds only `fork/` to the review stack. The local tooling patch in `workspace.patch.gz` contains the active tool and port files, the compatibility changes their tests exercise, and the fork's build and retention settings. The historical tool archive under `original/` records earlier versions.

From the layered fork, create a disposable checkout to run the fork tools at their usual paths.

```sh
python3 fork/tools/materialize.py /tmp/pso-fork-checks
cd /tmp/pso-fork-checks
python3 -m unittest discover -s tools/tests -q
make -C ports/tests run
```

Choose a new destination for each snapshot. The workspace includes committed files from the selected ref and uses the local repository's Git objects. The fork settings are applied in a separate local commit in that workspace. The [previous fork CI workflow](workflows/fork-source-checks.yml) is stored here as a reference. GitHub discovers workflows under the repository's top-level `.github/workflows/` directory, so the archived workflow is inactive. The commands above run the local checks directly. The ordinary checkout uses the upstream-shaped build and tool settings. Use the existing working-fork checkout for workflows that need its configured remotes or build outputs.

When refreshing the layer, generate the tooling patch from the matching review-stack and working-fork commits. Keep the native review changes on the review stack and fork workflow definitions under `fork/tooling/workflows/`.

```sh
git diff --binary --full-index --no-renames great-merge/current/review-stack \
  great-merge/current/working-fork -- . ':(exclude)fork' ':(exclude).github' \
  | gzip -n > fork/tooling/workspace.patch.gz
```

Run `python3 fork/tools/check_layer.py --upstream great-merge/current/review-stack --expect-clean` on the layered branch to verify that it adds only the fork layer.
