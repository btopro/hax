<?php

/**
 * @file
 * Hax Element type editing UI.
 */

/**
 * UI controller.
 */
class HaxElementTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Hax Element entity types, including adding and removing fields and the display of fields.';

    return $items;
  }
}

/**
 * Generates the Hax Element type editing form.
 */
function hax_element_type_form($form, &$form_state, $hax_element_type, $op = 'edit') {
  if ($op == 'clone') {
    $hax_element_type->label .= ' (cloned)';
    $hax_element_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $hax_element_type->label,
    '#description' => t('The human-readable name of this Hax Element type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($hax_element_type->type) ? $hax_element_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'hax_element_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Hax Element type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Hax Element type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function hax_element_type_form_submit(&$form, &$form_state) {
  $hax_element_type = entity_ui_form_submit_build_entity($form, $form_state);
  $hax_element_type->save();
  $form_state['redirect'] = 'admin/structure/hax_element_types';
}

/**
 * Form API submit callback for the delete button.
 */
function hax_element_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/hax_element_types/manage/' . $form_state['hax_element_type']->type . '/delete';
}
