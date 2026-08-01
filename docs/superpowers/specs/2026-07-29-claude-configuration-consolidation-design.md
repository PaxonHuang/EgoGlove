# Claude Code Configuration Consolidation Design

**Date:** 2026-07-29  
**Scope:** `/home/EchoGloveHugeProjects` Claude Code configuration and the active EgoGlove V7 workspace.  
**Status:** Approved for planning and implementation.

## Objective

Reduce default prompt and tool overhead while preserving all actively needed EgoGlove V7 engineering, research, frontend-validation, and embedded-hardware workflows. Treat the V6 Beta repository as a historical reference rather than a daily development target. Make every physical cleanup reversible through a dated archive and manifest before final deletion is considered.

## Scope and boundaries

### In scope

- Global, workspace, V7, and V6 `CLAUDE.md` instructions.
- Claude Code enabled-plugin configuration and project-local permissions/MCP declarations where present.
- V6-specific local skills and commands.
- Workspace memory files and their index.
- Historical graphify snapshots, stale backup candidates, and unused/redundant plugin cache candidates.
- Archival manifest, validation, and eventual user-approved commit/push.

### Out of scope

- V7 source, protocol specifications, tests, build configuration, or existing uncommitted Hand Token work.
- Credentials, authentication material, API keys, or environment secrets.
- Harness-provided runtime MCP tools that are not configured in the local/global Claude settings.
- Current V7 `graphify-out` output.
- Git push before the user reviews implementation outcomes and explicitly confirms the final push.

## Target operating model

### Retained V7 capabilities

The consolidated setup must retain these categories:

- Workflow and maintenance: `superpowers`, `remember`, `commit-commands`.
- Code quality and language intelligence: `code-simplifier`, `pyright-lsp`, `clangd-lsp`, `typescript-lsp`.
- Research: `context7` and web research facilities.
- Frontend/browser validation: `frontend-design`, `playwright`.
- Embedded workflows: ESP/PlatformIO, Espressif documentation, and ESP component-registry MCP facilities.
- Repository navigation: `graphify`, invoked for codebase questions and after code changes.

### Candidates to disable from the enabled default plugin set

Disable, but do not destroy, the following unless direct configuration inspection establishes that a retained workflow depends on one:

- `skill-creator`
- `hookify`
- `claude-md-management`
- `claude-code-setup`
- `jdtls-lsp`
- `cloudflare`

Other inactive marketplace/cache material is an archive candidate rather than an immediate deletion target.

### Runtime MCP boundary

Only MCP servers and tools declared by local/global configuration can be disabled here. The harness injects additional tools at runtime; those remain available regardless of local settings and must be reported honestly as outside this cleanup's control.

## Instruction consolidation

| File | Target | Content retained |
|---|---:|---|
| `/root/.claude/CLAUDE.md` | <=5 lines | Global graphify trigger only. |
| `/home/EchoGloveHugeProjects/CLAUDE.md` | <=15 lines | V7 active/V6 historical boundary and minimal graphify rules. |
| `EgoGlove/CLAUDE.md` | 30-40 lines | V7 truth sources, protocol/build/test constraints, Git identity discipline, minimal graphify workflow. |
| `EchoGlove-SLR-MOCAP-Beta/CLAUDE.md` | 15-25 lines | Historical/read-only boundary, minimal recovery guidance, and V7 pointer. |

Instructions that can be derived from scripts, README files, generated configuration, ordinary tool help, or source code are removed. No business/protocol code is modified by this work.

## V6 treatment

The V6 repository remains present as historical source reference. Its local daily-use automation is removed from the active configuration surface:

- Move `.claude/skills/phase/`, `.claude/skills/run-echoglove/`, and `.claude/commands/setup-env.md` into the dated archive.
- Replace the V6 guidance with a concise history/recovery pointer.
- Retain V6 source and any documentation required to understand or restore it.

## Memory consolidation

Keep a short active index and only durable, non-derivable V7 facts:

1. Hand Token v2 / Open Hand Motion Infrastructure.
2. V7 repository and source-of-truth pointer.
3. Git identity discipline.
4. Verified ecosystem/research anchors only if still useful.

Archive or merge duplicate project pointers, stale V6 overview material, completed task status, and content already maintained in V7 strategy/architecture documents or Git history. The index must link to files rather than duplicate their contents. Target total memory injection is <=17.6k tokens, from the reported 25.1k-token baseline.

## Reversible archive protocol

Create a dated archive outside routine configuration discovery. Before moving any candidate, create `MANIFEST.md` with:

- Original path and archive path.
- Classification (plugin cache, V6 skill/command, graph snapshot, memory backup, or config backup).
- Reason for archival.
- Exact restoration command or move-back instruction.
- Hash and byte count when practical.
- Status: archived, retained, or approved deletion candidate.

Archive configuration backups, V6-specific automation, old graphify snapshots, stale backup candidates, and unused/redundant plugin-cache candidates. Do not archive credentials, V7 source, current V7 graph output, or unknown items whose ownership/use cannot be verified.

## Validation

After implementation:

1. Validate every modified JSON configuration file.
2. Measure instructions and memory before/after; confirm instruction text is reduced by at least 50% and memory target is met or explain any shortfall.
3. Confirm retained plugins and local capabilities still resolve.
4. Confirm disabled plugins no longer appear in the enabled configuration.
5. Confirm V6 historical pointers are readable and all moved items are present in the archive manifest.
6. Check both repositories' Git status and ensure unrelated Hand Token changes remain untouched.
7. Run `graphify update .` only if a V7 tracked source/config change requires graph refresh, per project instructions; do not let generated graph output obscure the intended configuration diff.

## Release gates

1. Present the archive manifest and concise change summary to the user.
2. Wait for explicit confirmation before any final deletion outside the archive.
3. Wait for explicit confirmation before committing/pushing. Use the repository's documented Git identity discipline and do not add AI co-author signatures.
