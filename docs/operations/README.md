# Queue and tool operations

These references describe local tooling and its evidence contracts. They do not
report current queue state, authorize an action, or establish that a source change
has been installed in a live queue.

- [Local evidence and handoff tools](handoffs.md): comparison, snapshot reporting,
  durable routing, and the optional released-development resume adapter.
- [Reviewed local merge batches](../merge-batch.md): selecting and operating batches.
- [Source maintenance](../source-maintenance-queue.md): zero-gain source repairs.
- [Symbol renames](../symbol-rename-queue.md): bounded ABI metadata changes.
- [Atomic README measurements](../atomic-readme-queue.md): aggregate progress publication.

Human contribution instructions remain in the [contributor guides](../contributors/README.md).
Keep temporary snapshots, worker status, journals, original assets, raw reports,
private paths and build logs local. Publish reusable instructions or source-safe
investigation notes only when they add lasting project value; this directory is
not a destination for copying private handoff packets.
