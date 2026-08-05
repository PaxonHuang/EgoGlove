# CodeBaseMemory Migration Milestone — 2026-08-05

## Purpose

This note records the repository-local migration from Graphify as the active project-intelligence workflow to CodeBaseMemory MCP (CBM). It does not rename the project, change product strategy, alter GitHub identity, or modify protocol, firmware, tests, or frozen V7 architecture decisions.

## Graphify Role

Graphify was previously the default repository knowledge workflow and generated project graphs under `graphify-out/` and `relay/graphify-out/`. It is retired from the repository-local operational workflow, but is not uninstalled.

The following historical artifacts remain in place and are intentionally preserved:

- `graphify-out/`
- `graphify-out/2026-08-04/`
- `relay/graphify-out/`

They are generated historical evidence, not the authoritative source for current architecture or implementation status. No deletion, archival relocation, hook cleanup, global setting change, or uninstall is included in this milestone.

## CBM Replacement Rationale

CBM provides a dedicated repository index at:

```text
project: home-EchoGloveHugeProjects-EgoGlove
root:    /home/EchoGloveHugeProjects/EgoGlove
status:  ready
```

The parent workspace index was retained but was not selected as the default because broad queries could surface unrelated workspace projects and scoped natural-language retrieval was incomplete. The dedicated index is the repository knowledge layer for future work.

CBM separates the two main retrieval modes:

- **Code structure and relationships:** `get_architecture`, `search_graph`, `trace_path`, and `get_code_snippet`.
- **Strategic, roadmap, and interoperability documentation:** `search_code` constrained to Markdown files and the relevant `docs/` path.

This distinction prevents code-symbol ranking from being mistaken for a complete answer to documentation-first questions.

## New AI Development Workflow

1. Start with the dedicated CBM project `home-EchoGloveHugeProjects-EgoGlove`.
2. For structural questions, locate symbols with `search_graph` or map modules with `get_architecture`; trace dependencies with `trace_path`.
3. For Hand Token, product roadmap, adapter policy, or ecosystem facts, use `search_code` with `file_pattern="*.md"` and paths under `docs/V7`, `docs/BP`, or `docs/superpowers/specs`.
4. Verify strategic claims against `docs/V7/STRATEGY.md`; verify implementation status against `docs/V7/ARCHITECTURE.md`, source files, and tests.
5. Refresh the CBM index deliberately after meaningful tracked source/document changes. Do not treat generated Graphify output, build artifacts, or session logs as primary architecture evidence.

## Boundaries and Future Gate

This milestone changes only repository-local knowledge-workflow documentation. Global MCP registration at `/root/.claude/.mcp.json` is unchanged. Graphify removal beyond workflow retirement requires a separate explicit decision with query-parity evidence and a rollback plan.

Brand migration, GitHub rename, and broader EgoMotion repository migration have not started.
