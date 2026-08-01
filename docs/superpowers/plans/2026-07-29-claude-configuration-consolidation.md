# Claude Configuration Consolidation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Reduce Claude Code default context/tool overhead for the active EgoGlove V7 workspace, archive V6-only automation and stale artifacts reversibly, and validate the resulting setup without changing product code or pushing.

**Architecture:** Keep only the V7 engineering, research, frontend validation, and ESP/PlatformIO capability baseline enabled. Move—not delete—historical V6 Claude assets, dated graph snapshots, and disabled plugin cache candidates into a dated archive with a manifest and hashes. Compress instruction and memory layers so they link to source documents rather than duplicate them.

**Tech Stack:** Claude Code JSON/Markdown configuration, Bash, Python 3 standard library, Git, graphify.

## Global Constraints

- Do not modify V7 firmware, relay, models, SDK, data, web, tests, protocol implementation, credentials, or API keys.
- Do not reset, checkout, discard, rewrite history, commit, or push without a separate explicit user confirmation.
- Preserve `PaxonHuang <quenchkidney@outlook.com>` and the prohibition on AI co-author signatures in V7 guidance.
- Preserve V7 truth sources `docs/V7/STRATEGY.md`, `docs/V7/ARCHITECTURE.md`, and `docs/V7/README.md`.
- Preserve V7 engineering, research, frontend validation, ESP/PlatformIO, graphify, and memory workflows.
- Do not claim locally configured changes can uninstall harness-provided runtime MCP tools.
- Archive first; only a user-approved later operation may permanently remove an archived item.
- Keep current V7 `graphify-out` root output; archive only dated snapshots.

---

## File Map

| Path | Action | Responsibility |
|---|---|---|
| `/root/.claude/settings.json` | Modify + archive copy | Retain the 10-plugin V7 capability baseline; disable six unrelated defaults. |
| `/home/EchoGloveHugeProjects/CLAUDE.md` | Modify | Cross-repository navigation and graphify rules only. |
| `/home/EchoGloveHugeProjects/EgoGlove/CLAUDE.md` | Modify | Compact V7 operating contract. |
| `/home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/CLAUDE.md` | Modify | Historical/read-only recovery pointer. |
| `/home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/{skills,commands}` | Move to archive | Remove V6-only daily skills and command surface. |
| `/home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.agents/skills` | Move to archive | Remove V6-only custom embedded agent definitions. |
| `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/` | Modify/archive selected files | Keep durable V7 facts and remove duplicate V6/strategy pointers. |
| `/home/EchoGloveHugeProjects/EgoGlove/graphify-out/2026-07-{28,29}` | Move to archive | Remove stale dated graph snapshots while retaining active root output. |
| `/root/.claude/plugins/cache/*` selected inactive entries | Move to archive | Recover disk space without removing retained-plugin cache. |
| `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/MANIFEST.md` | Create | Maps every archived item to origin, purpose, hash, and restoration command. |
| `EgoGlove/docs/superpowers/{specs,plans}/2026-07-29-claude-configuration-consolidation-*.md` | Create | Approved design and execution record. |

## Retained Enabled Plugins

```json
[
  "frontend-design@claude-plugins-official",
  "superpowers@claude-plugins-official",
  "context7@claude-plugins-official",
  "code-simplifier@claude-plugins-official",
  "playwright@claude-plugins-official",
  "typescript-lsp@claude-plugins-official",
  "commit-commands@claude-plugins-official",
  "pyright-lsp@claude-plugins-official",
  "remember@claude-plugins-official",
  "clangd-lsp@claude-plugins-official"
]
```

## Disabled-Then-Archived Plugin Candidates

```json
[
  "skill-creator@claude-plugins-official",
  "claude-md-management@claude-plugins-official",
  "claude-code-setup@claude-plugins-official",
  "hookify@claude-plugins-official",
  "jdtls-lsp@claude-plugins-official",
  "cloudflare@claude-plugins-official"
]
```

### Task 1: Create the reversible archive and baseline manifest

**Files:**
- Create: `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/MANIFEST.md`
- Create: `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/baseline.json`

**Interfaces:**
- Consumes: existing file paths and enabled-plugin map.
- Produces: an archive root plus a machine-readable, secret-free inventory of planned moves.

- [ ] **Step 1: Capture before-state metadata without credentials**

Run this script. It writes only counts, paths, plugin names, Git short status, and SHA-256 values; it never serializes settings `env` values:

```bash
python3 - <<'PY'
import hashlib, json, pathlib, subprocess
archive = pathlib.Path('/home/EchoGloveHugeProjects/.claude-archive/2026-07-29')
archive.mkdir(parents=True, exist_ok=False)
settings = json.loads(pathlib.Path('/root/.claude/settings.json').read_text())
def digest(path):
    h = hashlib.sha256()
    with open(path, 'rb') as f:
        for block in iter(lambda: f.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()
baseline = {
  'enabled_plugins': sorted(k for k, v in settings['enabledPlugins'].items() if v),
  'global_settings_sha256': digest('/root/.claude/settings.json'),
  'workspace_settings_sha256': digest('/home/EchoGloveHugeProjects/.claude/settings.local.json'),
  'v7_status': subprocess.check_output(['git','-C','/home/EchoGloveHugeProjects/EgoGlove','status','--short'], text=True),
  'v6_status': subprocess.check_output(['git','-C','/home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta','status','--short'], text=True),
}
(archive / 'baseline.json').write_text(json.dumps(baseline, indent=2) + '\n')
PY
```

Expected: archive root exists and `baseline.json` contains no `ANTHROPIC_` values.

- [ ] **Step 2: Create a manifest header and write each item before moving it**

Create `MANIFEST.md` with columns: `Status`, `Category`, `Original path`, `Archive path`, `SHA-256`, `Reason`, `Restore`. Use `archived` only after a successful move and `retained` for active root graph output and V7 assets.

- [ ] **Step 3: Validate archive inventory is non-secret**

Run:

```bash
python3 -m json.tool /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/baseline.json >/dev/null
rg -n 'sk-[A-Za-z0-9_-]{8,}|ANTHROPIC_AUTH_TOKEN|ANTHROPIC_BASE_URL' /home/EchoGloveHugeProjects/.claude-archive/2026-07-29 || true
```

Expected: valid JSON and no credential values or keys in archive records.

### Task 2: Disable unused plugins while retaining V7 capability baseline

**Files:**
- Modify: `/root/.claude/settings.json`
- Archive copy: `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/global-settings/settings.json`

**Interfaces:**
- Consumes: existing `env`, `theme`, `attribution`, and `enabledPlugins` fields.
- Produces: same non-plugin fields, with exactly the retained 10 plugins set `true` and six candidates set `false`.

- [ ] **Step 1: Archive a byte-for-byte settings copy**

```bash
mkdir -p /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/global-settings
cp -p /root/.claude/settings.json /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/global-settings/settings.json
```

- [ ] **Step 2: Rewrite only `enabledPlugins` deterministically**

```bash
python3 - <<'PY'
import json
from pathlib import Path
p = Path('/root/.claude/settings.json')
d = json.loads(p.read_text())
retained = {
 'frontend-design@claude-plugins-official', 'superpowers@claude-plugins-official',
 'context7@claude-plugins-official', 'code-simplifier@claude-plugins-official',
 'playwright@claude-plugins-official', 'typescript-lsp@claude-plugins-official',
 'commit-commands@claude-plugins-official', 'pyright-lsp@claude-plugins-official',
 'remember@claude-plugins-official', 'clangd-lsp@claude-plugins-official',
}
d['enabledPlugins'] = {k: k in retained for k in d['enabledPlugins']}
p.write_text(json.dumps(d, indent=2) + '\n')
PY
```

- [ ] **Step 3: Validate exact plugin split and untouched top-level fields**

```bash
python3 - <<'PY'
import json
p='/root/.claude/settings.json'; d=json.load(open(p))
assert set(d) == {'env','theme','attribution','enabledPlugins'}
on=sorted(k for k,v in d['enabledPlugins'].items() if v)
off=sorted(k for k,v in d['enabledPlugins'].items() if not v)
assert len(on) == 10, on
assert off == [
 'claude-code-setup@claude-plugins-official', 'claude-md-management@claude-plugins-official',
 'cloudflare@claude-plugins-official', 'hookify@claude-plugins-official',
 'jdtls-lsp@claude-plugins-official', 'skill-creator@claude-plugins-official'
], off
print('enabled:', *on, sep='\n- ')
print('disabled:', *off, sep='\n- ')
PY
```

Expected: exactly 10 enabled and six disabled plugins; no `env` value is printed.

### Task 3: Consolidate instruction layers and historical V6 entry point

**Files:**
- Modify: `/home/EchoGloveHugeProjects/CLAUDE.md`
- Modify: `/home/EchoGloveHugeProjects/EgoGlove/CLAUDE.md`
- Modify: `/home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/CLAUDE.md`
- Archive copy: corresponding files under `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/instructions/`

**Interfaces:**
- Consumes: V7 source-of-truth requirements and V6 historical-only designation.
- Produces: <=15-line workspace guide, <=45-line V7 guide, and <=25-line V6 history pointer.

- [ ] **Step 1: Archive original instruction files**

```bash
mkdir -p /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/instructions
cp -p /home/EchoGloveHugeProjects/CLAUDE.md /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/instructions/workspace-CLAUDE.md
cp -p /home/EchoGloveHugeProjects/EgoGlove/CLAUDE.md /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/instructions/v7-CLAUDE.md
cp -p /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/CLAUDE.md /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/instructions/v6-CLAUDE.md
```

- [ ] **Step 2: Replace workspace instructions with repository routing only**

Write this exact content to `/home/EchoGloveHugeProjects/CLAUDE.md`:

```markdown
# Workspace Guide

- `EgoGlove/` is the active V7 repository. `EchoGlove-SLR-MOCAP-Beta/` is historical, read-only reference unless the user explicitly requests V6 work.
- For EgoGlove codebase questions, use `graphify query` when `graphify-out/graph.json` exists; use `path`/`explain` for relationships and `wiki/index.md` for broad navigation.
- Read `GRAPH_REPORT.md` only for broad architecture review or when scoped graph queries are insufficient.
- After modifying EgoGlove code or project documentation, run `graphify update .` from `EgoGlove/`.
```

- [ ] **Step 3: Replace V7 instructions with the compact operating contract**

Include exactly these concepts: project purpose; V7 source documents; repository map; `main ← develop ← feature/*`; required Git identity; no AI co-author; no push without instruction; four truth labels; Hand Token v2 canonical-20/FK-21/TLV constraint; major-decision escalation; graphify workflow; targeted validation; and V6 as historical reference. Do not replicate source-document tables, architecture diagrams, or build recipes.

- [ ] **Step 4: Replace V6 instructions with historical recovery guidance**

Write a short guide stating V6 is historical/read-only, V7 is active, V6 source must not be migrated without explicit approval, and archived V6 skills/commands can be restored from the dated archive manifest.

- [ ] **Step 5: Validate sizes and non-negotiable V7 constraints**

```bash
wc -l /home/EchoGloveHugeProjects/CLAUDE.md /home/EchoGloveHugeProjects/EgoGlove/CLAUDE.md /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/CLAUDE.md
rg -n 'PaxonHuang|quenchkidney@outlook.com|AI co-author|未经.*push|已实现|工程可实现|需研发验证|长期方向|canonical-20|FK-21|TLV|graphify' /home/EchoGloveHugeProjects/EgoGlove/CLAUDE.md
```

Expected: line counts at or below 15/45/25, and every V7 constraint is found.

### Task 4: Archive V6-only skills, commands, and custom agents

**Files:**
- Move: `EchoGlove-SLR-MOCAP-Beta/.claude/skills/phase/`
- Move: `EchoGlove-SLR-MOCAP-Beta/.claude/skills/run-echoglove/`
- Move: `EchoGlove-SLR-MOCAP-Beta/.claude/commands/setup-env.md`
- Move: `EchoGlove-SLR-MOCAP-Beta/.agents/skills/`
- Destination: `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/v6-automation/`

**Interfaces:**
- Consumes: V6 historical-only decision.
- Produces: no active V6 local skills, commands, or custom agent definitions; full tree restorable from manifest.

- [ ] **Step 1: Hash each source tree and add pending manifest entries**

Use:

```bash
sha256sum $(find /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/skills /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/commands /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.agents/skills -type f | sort) > /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/v6-automation.sha256
```

- [ ] **Step 2: Move the V6 daily automation atomically by top-level directory**

```bash
mkdir -p /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/v6-automation/.claude /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/v6-automation/.agents
mv /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/skills /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/v6-automation/.claude/skills
mv /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/commands /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/v6-automation/.claude/commands
mv /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.agents/skills /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/v6-automation/.agents/skills
```

- [ ] **Step 3: Verify absence at source and tree/hash preservation in archive**

```bash
test ! -e /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/skills
test ! -e /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/commands
test ! -e /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.agents/skills
(cd /home/EchoGloveHugeProjects/.claude-archive/2026-07-29 && sha256sum -c v6-automation.sha256)
```

Expected: all source paths absent; every hash verifies. If archive root path causes relative-path verification failure, verify using an absolute-path `sha256sum -c` file regenerated after the move.

### Task 5: Consolidate active memories and archive stale pointers

**Files:**
- Modify: `/root/.claude/projects/-home-EchoGloveHugeProjects/memory/MEMORY.md`
- Modify: `handtoken-v2-open-hand-infra.md`, `echoglove-bp-task.md`, `git-identity-discipline.md`, `echoglove-ecosystem-anchors.md`
- Move: `echoglove-project-overview.md`, `echoglove-strategy-frozen.md`, `egoglove-monorepo-v7.md`
- Destination: `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/memory/`

**Interfaces:**
- Consumes: V7 source documents and durable facts not derived from Git/docs.
- Produces: four-file index with no repeated strategy/architecture content, plus archived original pointer files.

- [ ] **Step 1: Archive the complete current memory directory first**

```bash
mkdir -p /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/memory/pre-consolidation
cp -a /root/.claude/projects/-home-EchoGloveHugeProjects/memory/. /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/memory/pre-consolidation/
```

- [ ] **Step 2: Replace `MEMORY.md` with four valid active links**

```markdown
# Memory Index

- [Hand Token v2 / Open Hand Motion Infra](handtoken-v2-open-hand-infra.md) — durable protocol state and implementation gates
- [BP task](echoglove-bp-task.md) — remaining business-plan review/package work
- [Git identity discipline](git-identity-discipline.md) — required commit identity and no AI co-author signatures
- [OSS ecosystem anchors](echoglove-ecosystem-anchors.md) — externally verified interoperability and licensing facts
```

- [ ] **Step 3: Compact durable memories and move duplicate pointers to archive**

Keep frontmatter in each retained memory. Replace details derived from `STRATEGY.md`, `ARCHITECTURE.md`, Git history, or completed temporary work with concise source pointers. Move the three pointer files to `memory/retired-pointers/`, preserving their original names.

- [ ] **Step 4: Validate links, format, and size reduction**

```bash
python3 - <<'PY'
import pathlib, re
root=pathlib.Path('/root/.claude/projects/-home-EchoGloveHugeProjects/memory')
index=(root/'MEMORY.md').read_text()
links=re.findall(r'\]\(([^)]+\.md)\)', index)
assert len(links) == 4, links
assert all((root / link).is_file() for link in links), links
for link in links:
    text=(root/link).read_text()
    assert text.startswith('---\n'), link
print('valid memory links:', links)
print('active_bytes:', sum(p.stat().st_size for p in root.glob('*.md')))
PY
```

Expected: exactly four working index links and total active memory substantially below the 13,202-byte baseline.

### Task 6: Archive stale graph snapshots and inactive plugin caches

**Files:**
- Move: `EgoGlove/graphify-out/2026-07-28/`, `EgoGlove/graphify-out/2026-07-29/`
- Move selected cache directories: `academic-research-skills/`, `carbone-skill/`, `claude-code-setup/`, `claude-md-management/`, `cloudflare/`, `github/`, `hookify/`, `jdtls-lsp/`, `ralph-loop/`, `skill-creator/`, `temp_git_*`
- Destination: `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/{graphify-snapshots,plugin-cache}/`

**Interfaces:**
- Consumes: selected inactive plugin/cache list and active root graph output.
- Produces: retained current root graph, archive copies of stale snapshots/caches, and restorability records.

- [ ] **Step 1: Confirm root graph output exists and snapshots are dated subdirectories**

```bash
test -f /home/EchoGloveHugeProjects/EgoGlove/graphify-out/graph.json
test -f /home/EchoGloveHugeProjects/EgoGlove/graphify-out/GRAPH_REPORT.md
test -d /home/EchoGloveHugeProjects/EgoGlove/graphify-out/2026-07-28
test -d /home/EchoGloveHugeProjects/EgoGlove/graphify-out/2026-07-29
```

- [ ] **Step 2: Move only dated snapshots**

```bash
mkdir -p /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/graphify-snapshots
mv /home/EchoGloveHugeProjects/EgoGlove/graphify-out/2026-07-28 /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/graphify-snapshots/
mv /home/EchoGloveHugeProjects/EgoGlove/graphify-out/2026-07-29 /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/graphify-snapshots/
```

- [ ] **Step 3: Move inactive cache entries without touching retained plugin caches**

Move exact directories if present, using `mv` to the archive: `/root/.claude/plugins/cache/academic-research-skills`, and under `/root/.claude/plugins/cache/claude-plugins-official/`: `carbone-skill`, `claude-code-setup`, `claude-md-management`, `cloudflare`, `github`, `hookify`, `jdtls-lsp`, `ralph-loop`, `skill-creator`. Move `/root/.claude/plugins/cache/temp_git_1784707096698_yc90j8` and `temp_git_1785255249807_6ol78l`. Do not move the ten retained plugin cache directories.

- [ ] **Step 4: Validate retained graph and cache set**

```bash
test -f /home/EchoGloveHugeProjects/EgoGlove/graphify-out/graph.json
test -f /home/EchoGloveHugeProjects/EgoGlove/graphify-out/GRAPH_REPORT.md
for p in frontend-design superpowers context7 code-simplifier playwright typescript-lsp commit-commands pyright-lsp remember clangd-lsp; do test -d "/root/.claude/plugins/cache/claude-plugins-official/$p"; done
for p in skill-creator claude-md-management claude-code-setup hookify jdtls-lsp cloudflare; do test ! -e "/root/.claude/plugins/cache/claude-plugins-official/$p"; done
```

Expected: current graph output and all retained caches remain available; disabled caches are absent from active cache locations.

### Task 7: Final manifest, configuration checks, graph refresh, and report

**Files:**
- Modify: `/home/EchoGloveHugeProjects/.claude-archive/2026-07-29/MANIFEST.md`
- Modify generated: `EgoGlove/graphify-out/*` only through `graphify update .`

**Interfaces:**
- Consumes: every archive move and modified configuration.
- Produces: complete restoration instructions, validated configuration, fresh V7 graph, and a no-push completion report.

- [ ] **Step 1: Add archive rows with digest and exact restoration command**

For every moved top-level item, use a command of this form in the manifest:

```bash
mv /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/v6-automation/.claude/skills /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/skills
```

For settings restoration, record:

```bash
cp -p /home/EchoGloveHugeProjects/.claude-archive/2026-07-29/global-settings/settings.json /root/.claude/settings.json
```

- [ ] **Step 2: Validate all modified JSON and active plugin configuration**

```bash
python3 -m json.tool /root/.claude/settings.json >/dev/null
python3 -m json.tool /home/EchoGloveHugeProjects/.claude/settings.json >/dev/null
python3 -m json.tool /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/.claude/settings.json >/dev/null
python3 - <<'PY'
import json
p='/root/.claude/settings.json'; d=json.load(open(p))
assert sum(d['enabledPlugins'].values()) == 10
assert not any(d['enabledPlugins'][x] for x in [
 'skill-creator@claude-plugins-official','claude-md-management@claude-plugins-official',
 'claude-code-setup@claude-plugins-official','hookify@claude-plugins-official',
 'jdtls-lsp@claude-plugins-official','cloudflare@claude-plugins-official'])
print('plugin configuration valid')
PY
```

- [ ] **Step 3: Refresh V7 graph because V7 instruction/docs changed**

```bash
cd /home/EchoGloveHugeProjects/EgoGlove && graphify update .
```

Expected: command succeeds; current `graphify-out` becomes current without restoring dated snapshots.

- [ ] **Step 4: Check changes remain within scope**

```bash
git -C /home/EchoGloveHugeProjects/EgoGlove status --short
git -C /home/EchoGloveHugeProjects/EgoGlove diff --check
git -C /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta status --short
find /home/EchoGloveHugeProjects/.claude-archive/2026-07-29 -type f | wc -l
```

Expected: V7 source-code changes remain only the pre-existing Hand Token changes; this work changes only configuration/docs/graph artifacts. V6 changes are confined to its guide and removed local automation. No commit/push occurs.

- [ ] **Step 5: Present the archive manifest, retention summary, metrics, and final-delete candidates to the user**

Report instruction line-count reduction, active-memory byte reduction, enabled/disabled plugin lists, archive location/size, V6 historical conversion, graph refresh result, validation output, and the explicit limitation that harness-injected MCP tools remain outside local configuration control. Ask for explicit approval before any final deletion or Git commit/push.
