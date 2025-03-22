struct irq_data {
  struct irq_domain *domain;
} irq_domain_fix_revmap_d;
struct irq_domain {
  struct irq_domain *parent;
  int revmap_size;
  struct irq_data *revmap[10];
};
long irq_domain_fix_revmap_d_0;
int irq_domain_pop_irq() {
  irq_domain_fix_revmap_d.domain->revmap[irq_domain_fix_revmap_d_0] = 0;
  return 0;
}
